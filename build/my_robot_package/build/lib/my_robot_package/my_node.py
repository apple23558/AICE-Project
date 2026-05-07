# Improved ROS2 Block Sorter
#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image, LaserScan
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry

from cv_bridge import CvBridge
import cv2
import numpy as np
import math


class BlockSorter(Node):

    CENTER_X = 0.0
    DELIVERY_TARGET = 0.1

    PUSH_YAW = {
        "RED": 0.0,
        "BLUE": math.pi
    }

    def __init__(self):
        super().__init__('block_sorter')

        self.create_subscription(Image, '/camera/image_raw', self.image_callback, 10)
        self.create_subscription(LaserScan, '/scan', self.scan_callback, 10)
        self.create_subscription(Odometry, '/odom', self.odom_callback, 10)

        self.cmd_pub = self.create_publisher(Twist, '/cmd_vel', 10)
        self.timer = self.create_timer(0.1, self.control_loop)

        self.bridge = CvBridge()

        # STATE MACHINE
        self.state = "SEARCH"

        # VISION MEMORY
        self.last_seen_counter = 0
        self.block_detected = False

        self.block_color = None
        self.block_center_x = 0
        self.block_distance = float('inf')
        self.block_angle = 0.0

        # LIDAR
        self.front_distance = float('inf')

        # ODOM
        self.x = 0.0
        self.y = 0.0
        self.yaw = 0.0

        # 🔧 STALL DETECTION (NEW)
        self.stall_counter = 0
        self.last_x = 0.0
        self.last_y = 0.0

        # PUSH TRACKING
        self.push_color = None
        self.push_timeout = 0

        # COMPLETED BLOCK COUNTS
        self.red_done = 0
        self.blue_done = 0

        # SEARCH
        self.search_steps = 0

        # BACKUP
        self.backup_steps = 0

        self.get_logger().info("Improved block sorter started")

    # ==========================================================
    # CAMERA CALLBACK
    # ==========================================================

    def image_callback(self, msg):

        if self.state == "PUSHING":
            return

        frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        red_mask1 = cv2.inRange(hsv, np.array([0, 120, 70]), np.array([10, 255, 255]))
        red_mask2 = cv2.inRange(hsv, np.array([170, 120, 70]), np.array([180, 255, 255]))
        red_mask = red_mask1 + red_mask2

        blue_mask = cv2.inRange(hsv, np.array([100, 150, 0]), np.array([140, 255, 255]))

        mask = red_mask + blue_mask

        contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        if contours:

            largest = max(contours, key=cv2.contourArea)

            if cv2.contourArea(largest) > 1200:

                x, y, w, h = cv2.boundingRect(largest)

                self.block_center_x = x + w / 2

                image_width = frame.shape[1]
                fov = 60.0

                self.block_angle = (
                    (self.block_center_x - image_width / 2) / image_width
                ) * fov

                red_score = cv2.mean(red_mask[y:y+h, x:x+w])[0]
                blue_score = cv2.mean(blue_mask[y:y+h, x:x+w])[0]

                if red_score > blue_score:
                    self.block_color = "RED"
                    if self.x > 0:
                        self.block_detected = False
                        return
                else:
                    self.block_color = "BLUE"
                    if self.x < 0:
                        self.block_detected = False
                        return

                self.block_detected = True

                # reset vision watchdog
                self.last_seen_counter = 0

                self.block_distance = self.front_distance
                return

        self.block_detected = False

    # ==========================================================
    # LIDAR CALLBACK
    # ==========================================================

    def scan_callback(self, msg):

        ranges = np.array(msg.ranges)

        center = len(ranges) // 2
        window = 25

        front_slice = ranges[center-window:center+window]
        front_slice = front_slice[np.isfinite(front_slice)]

        if len(front_slice) > 0:
            self.front_distance = float(np.min(front_slice))
        else:
            self.front_distance = float('inf')

    # ==========================================================
    # ODOM CALLBACK
    # ==========================================================

    def odom_callback(self, msg):

        self.x = msg.pose.pose.position.x
        self.y = msg.pose.pose.position.y

        q = msg.pose.pose.orientation

        siny = 2 * (q.w * q.z + q.x * q.y)
        cosy = 1 - 2 * (q.y * q.y + q.z * q.z)

        self.yaw = math.atan2(siny, cosy)

    # ==========================================================
    # HELPERS
    # ==========================================================

    def yaw_error(self, target_yaw):

        err = target_yaw - self.yaw

        while err > math.pi:
            err -= 2 * math.pi

        while err < -math.pi:
            err += 2 * math.pi

        return err

    def block_delivered(self):

        if self.push_color == "RED":
            if self.x > 0.45:
                self.red_done += 1
                return True

        elif self.push_color == "BLUE":
            if self.x < -0.45:
                self.blue_done += 1
                return True

        return False

    # ==========================================================
    # CONTROL LOOP
    # ==========================================================

    def control_loop(self):

        twist = Twist()

        # ======================================================
        # VISION WATCHDOG
        # ======================================================
        self.last_seen_counter += 1
        if self.last_seen_counter > 10:
            self.block_detected = False

        # ======================================================
        # STOP CONDITION
        # ======================================================
        if self.red_done >= 2 and self.blue_done >= 2:
            self.get_logger().info("ALL BLOCKS SORTED")
            self.cmd_pub.publish(Twist())
            return

        # ======================================================
        # SEARCH
        # ======================================================
        if self.state == "SEARCH":

            self.search_steps += 1

            if self.front_distance < 0.25:
                twist.linear.x = -0.05
                twist.angular.z = 1.5

            elif self.search_steps % 40 < 12:
                twist.linear.x = 0.20

            else:
                twist.angular.z = 0.9

            if self.block_detected:
                self.state = "ALIGN"
                self.search_steps = 0

        # ======================================================
        # ALIGN
        # ======================================================
        elif self.state == "ALIGN":

            if abs(self.block_angle) > 3.0:
                twist.angular.z = -0.03 * self.block_angle
            else:
                self.state = "APPROACH"

        # ======================================================
        # APPROACH
        # ======================================================
        elif self.state == "APPROACH":

            twist.angular.z = -0.015 * self.block_angle

            if self.front_distance > 0.32:
                twist.linear.x = 0.18
            else:
                self.state = "PUSH"

        # ======================================================
        # PUSH INIT
        # ======================================================
        elif self.state == "PUSH":

            self.push_color = self.block_color
            self.push_timeout = 0
            self.stall_counter = 0

            self.get_logger().info(f"Starting push: {self.push_color}")

            self.state = "PUSHING"

        # ======================================================
        # PUSHING (STALL FIX ADDED)
        # ======================================================
        elif self.state == "PUSHING":

            self.push_timeout += 1

            # ---------------- STALL DETECTION ----------------
            movement = abs(self.x - self.last_x) + abs(self.y - self.last_y)

            if self.front_distance < 0.15 and movement < 0.001:
                self.stall_counter += 1
            else:
                self.stall_counter = 0

            self.last_x = self.x
            self.last_y = self.y

            # -------------------------------------------------

            target_yaw = self.PUSH_YAW.get(self.push_color, 0.0)
            yaw_err = self.yaw_error(target_yaw)

            twist.linear.x = 0.22
            twist.angular.z = max(min(0.4 * yaw_err, 0.3), -0.3)

            delivered = self.block_delivered()
            timed_out = self.push_timeout > 180
            stalled = self.stall_counter > 20

            if delivered or timed_out or stalled:

                reason = (
                    "DELIVERED" if delivered else
                    "TIMEOUT" if timed_out else
                    "STALLED"
                )

                self.get_logger().info(f"{self.push_color} block {reason}")

                self.backup_steps = 15
                self.state = "BACKUP"

        # ======================================================
        # BACKUP
        # ======================================================
        elif self.state == "BACKUP":

            twist.linear.x = -0.20

            self.backup_steps -= 1

            if self.backup_steps <= 0:

                self.block_detected = False
                self.block_color = None
                self.push_color = None

                self.state = "SEARCH"

        self.cmd_pub.publish(twist)


# ==============================================================
# MAIN
# ==============================================================

def main(args=None):

    rclpy.init(args=args)
    node = BlockSorter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()