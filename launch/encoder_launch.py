from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('parameters_file', default_value='/home/pedro/tfg_ws/src/tfg_repository/config/encoder_params.yaml',
                              description='Path to parameters YAML file'),

        Node(
            package='tfg_repository',
            executable='tfg_repository_encoder_node',
            name='encoder_node',
            output='screen',
            emulate_tty=True,
            parameters=[LaunchConfiguration('parameters_file')]
        )

    ])
