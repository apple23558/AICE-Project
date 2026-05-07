import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/aice/ros2_ws/src/my_robot_package/install/my_robot_package'
