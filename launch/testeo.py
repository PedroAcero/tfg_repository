from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition
from launch.actions import ExecuteProcess


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('drone_id', default_value='drone0'),
        DeclareLaunchArgument('use_sim_time', default_value='false'),
        DeclareLaunchArgument(
            'launch_pubsub', default_value='false', description='Launch PubSub node'),

        # Encoder
        ExecuteProcess(
            cmd=['xterm', '-e', 'ros2', 'run', 'tfg_repository',
                 'tfg_repository_encoder_node'],
            output='screen',
            additional_env={
                'use_sim_time': LaunchConfiguration('use_sim_time')},
            shell=True
        ),

        # Decoder
        ExecuteProcess(
            cmd=['xterm', '-e', 'ros2', 'run', 'tfg_repository', 'tfg_repository_decoder_node',
                 '--ros-args', '--params-file /home/pedro/tfg_ws/src/tfg_repository/config/comm_params.yaml'],
            output='screen',
            additional_env={
                'use_sim_time': LaunchConfiguration('use_sim_time')},
            shell=True
        ),

        # PubSub se lanza si se indica con la variable "launch_pubsub"
        ExecuteProcess(
            cmd=['xterm', '-e', 'ros2', 'run',
                 'tfg_repository', 'tfg_repository_pubsub_node'],
            output='screen',
            additional_env={
                'use_sim_time': LaunchConfiguration('use_sim_time')},
            shell=True,
            condition=IfCondition(LaunchConfiguration('launch_pubsub'))
        )
    ])
