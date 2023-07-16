from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('drone_id', default_value='drone0'),
        DeclareLaunchArgument('use_sim_time', default_value='false'),
        Node(
            package='as2_node_template',
            executable='as2_node_template_node',
            name='as2_node_template',
            namespace=LaunchConfiguration('drone_id'),
            parameters=[{'use_sim_time': LaunchConfiguration('use_sim_time')}],
            output='screen',
            emulate_tty=True
        )
    ])
