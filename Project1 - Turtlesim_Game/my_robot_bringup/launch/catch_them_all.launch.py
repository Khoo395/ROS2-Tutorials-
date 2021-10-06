from launch import LaunchDescription
from launch_ros.actions import Node



def generate_launch_description():
    ld = LaunchDescription()

    turtlesim_node = Node(
        package ="turtlesim",
        executable ="turtlesim_node",
       
    )

    turtle_spawner = Node(
        package ="turtlesim_catch_them_all",
        executable ="spawner",
       
    )
    turtle_controller = Node(
        package ="turtlesim_catch_them_all",
        executable ="controller",
        


    )
    ld.add_action(turtlesim_node)
    ld.add_action(turtle_spawner)
    ld.add_action(turtle_controller)
   
    return ld