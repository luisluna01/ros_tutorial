from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, GroupAction
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare, PushRosNamespace


def generate_launch_description():
    launch_dir = PathJoinSubstitution([FindPackageShare('launch_tutorial'), 'launch'])
    return LaunchDescription([
        IncludeLaunchDescription(
            PathJoinSubstitution([launch_dir, 'turtlesim_world_1.launch.py'])
        ),
        GroupAction(
            actions=[
                # Ensure every node, including nested nodes, inherit 'turtlesim2' namespace
                PushRosNamespace('turtlesim2'),
                IncludeLaunchDescription(
                    PathJoinSubstitution([launch_dir, 'turtlesim_world_2_launch.py'])),
            ]
        ),
        IncludeLaunchDescription(
            PathJoinSubstitution([launch_dir, 'turtlesim_world_3.launch.py'])
        ),
        IncludeLaunchDescription(
            PathJoinSubstitution([launch_dir, 'broadcaster_listener.launch.py']),
            # Parameter override
            launch_arguments={'target_frame': 'carrot1'}.items()
        ),
        IncludeLaunchDescription(
            PathJoinSubstitution([launch_dir, 'mimic.launch.py'])
        ),
        IncludeLaunchDescription(
            PathJoinSubstitution([launch_dir, 'fixed_broadcaster.launch.py'])
        ),
        IncludeLaunchDescription(
            PathJoinSubstitution([launch_dir, 'turtlesim_rviz.launch.py'])
        ),
    ])
