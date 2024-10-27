from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
import os
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    TimerAction
)
from launch.actions import RegisterEventHandler
from launch.event_handlers import OnProcessExit

def generate_launch_description():

    arm_world_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution(
                [FindPackageShare("arm_gazebo"), "launch", "arm_world.launch.py"]
            )
        )
    )

    arm_control_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution(
                [FindPackageShare("arm_control"), "launch", "arm_control.launch.py"]
            )
        )
    )

    delay_arm_control_launch = TimerAction(
        period=2.0,
        actions=[arm_control_launch]
    )

    nodes_to_start = [
       arm_world_launch,
       delay_arm_control_launch,
    ]

    return LaunchDescription(nodes_to_start)

