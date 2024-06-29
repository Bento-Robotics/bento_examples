from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():

    # use launch argument by appending my_parameter:='xxx' to launch command

    my_parameter = LaunchConfiguration('my_parameter')

    return LaunchDescription([
        DeclareLaunchArgument(
            'my_parameter',
            default_value='world',
            description='set parameter for first printed line'
        ),

        Node(
            package='cpp_parameters',
            executable='minimal_param_node',
            name='minimal_param_node',
            parameters=[{'my_parameter': my_parameter}],
        ),
  ])
