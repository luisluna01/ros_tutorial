# This launch file how to call and pass arguments to another launch file
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    colors = {
        'background_r': '200'
    }

    return LaunchDescription([
        IncludeLaunchDescription(
            # Join the path to launch_tutorial pkg, launch directory, and launch file
            PathJoinSubstitution([
                FindPackageShare('py_launch_tutorial'), # Find the path to the launch_tutorial pkg
                'launch',
                'substitutions.launch.py'
            ]),
            
            launch_arguments={
                'turtlesim_ns': 'turtlesim2',
                'use_provided_red': 'True',
                'new_background_r': colors['background_r'],
            }.items()
        )
    ])
