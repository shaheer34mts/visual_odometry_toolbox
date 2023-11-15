# visual_odometry_toolbox/launch/visual_odometry_toolbox_launch.py

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='visual_odometry_toolbox',
            executable='visual_odometry_node',
            output='screen',
        ),
    ])
