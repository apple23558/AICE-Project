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

    def __init__(self):
        super().__init__('block_sorter')

        # Subscribers
        self.create_subscription(Image, '/camera/image_raw', self.image_callback, 10)
        self.create_subscription(LaserScan, '/scan', self.scan_callback, 10)
        self.create_subscription(Odometry, '/odom', self.odom_callback, 10)

        # Publisher
        self.cmd_pub = self.create_publisher(Twist, '/cmd_vel', 10)

        # Timer loop
        self.create_timer(0.1, self.control_loop)

        self.bridge = CvBridge()

        # State machine
        self.state = "SEARCH"

        # Detection
        self.block_detected = False
        self.block_color = None
        self.block_center_x = 0

        # LiDAR
        self.front_distance = float('inf')

        # Robot pose
        self.x = 0.0
        self.y = 0.0
        self.yaw = 0.0

        # Drop zones (you can tune these)
        self.red_zone = (2.0, 2.0)
        self.blue_zone = (-2.0, 2.0)

        self.get_logger().info("Block sorter started")

    # -------------------------
    # SENSOR CALLBACKS
    # -------------------------

    def image_callback(self, msg):
        frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # Red mask
        red_lower = np.array([0, 120, 70])
        red_upper = np.array([10, 255, 255])
        red_mask = cv2.inRange(hsv, red_lower, red_upper)

        # Blue mask
        blue_lower = np.array([100, 150, 0])
        blue_upper = np.array([140, 255, 255])
        blue_mask = cv2.inRange(hsv, blue_lower, blue_upper)

        # Combine detections
        mask = red_mask + blue_mask

        contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

        if contours:
            largest = max(contours, key=cv2.contourArea)

            if cv2.contourArea(largest) > 500:
                x, y, w, h = cv2.boundingRect(largest)
                self.block_center_x = x + w / 2

                # Determine color
                if cv2.mean(red_mask[y:y+h, x:x+w])[0] > 50:
                    self.block_color = "RED"
                else:
                    self.block_color = "BLUE"

                self.block_detected = True
                return

        self.block_detected = False

    def scan_callback(self, msg):
        front = msg.ranges[len(msg.ranges)//2]
        self.front_distance = front

    def odom_callback(self, msg):
        self.x = msg.pose.pose.position.x
        self.y = msg.pose.pose.position.y

        q = msg.pose.pose.orientation
        siny = 2 * (q.w * q.z + q.x * q.y)
        cosy = 1 - 2 * (q.y * q.y + q.z * q.z)
        self.yaw = math.atan2(siny, cosy)

    # -------------------------
    # CONTROL LOOP
    # -------------------------

    def control_loop(self):
        twist = Twist()

        if self.state == "SEARCH":
            twist.angular.z = 0.5

            if self.block_detected:
                self.state = "ALIGN"

        elif self.state == "ALIGN":
            error = self.block_center_x - 320  # assume 640px width

            if abs(error) > 50:
                twist.angular.z = -0.002 * error
            else:
                self.state = "APPROACH"

        elif self.state == "APPROACH":
            if self.front_distance > 0.3:
                twist.linear.x = 0.15
            else:
                self.state = "PUSH"

        elif self.state == "PUSH":
            if self.front_distance > 0.15:
                twist.linear.x = 0.2
            else:
                self.state = "DELIVER"

        elif self.state == "DELIVER":
            self.navigate_to_zone()
            return

        self.cmd_pub.publish(twist)

    # -------------------------
    # NAVIGATION LOGIC
    # -------------------------

    def navigate_to_zone(self):
        twist = Twist()

        target = self.red_zone if self.block_color == "RED" else self.blue_zone

        dx = target[0] - self.x
        dy = target[1] - self.y

        distance = math.sqrt(dx**2 + dy**2)
        angle_to_goal = math.atan2(dy, dx)

        angle_error = angle_to_goal - self.yaw

        if abs(angle_error) > 0.2:
            twist.angular.z = 0.5 * angle_error
        elif distance > 0.2:
            twist.linear.x = 0.2
        else:
            self.get_logger().info(f"{self.block_color} block delivered!")
            self.state = "SEARCH"

        self.cmd_pub.publish(twist)


def main(args=None):
    rclpy.init(args=args)
    node = BlockSorter()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()