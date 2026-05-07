from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='my_robot_package',
            executable='my_node',
            name='my_renamed_node',
            output='screen',
            parameters=[{'use_sim_time': False}]
        ),
    ])