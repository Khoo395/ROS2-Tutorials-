from launch import LaunchDescription
from launch_ros.actions import Node

parameter_rename = ("Robot_Name","Robot_News")

def generate_launch_description():
    ld = LaunchDescription()
    Robot_News_S1 = Node(
        package ="my_cpp_pkg",
        executable ="robot_news",
        name = "Ai_FM",
        remappings={parameter_rename}
    )
    Robot_News_S2 = Node(
        package ="my_cpp_pkg",
        executable ="robot_news",
        name = "Fly_FM",
        remappings={parameter_rename}
    )
    Robot_News_S3 = Node(
        package ="my_cpp_pkg",
        executable ="robot_news",
        name = "One_FM",
        remappings={parameter_rename}
    )
    Robot_News_S4 = Node(
        package ="my_cpp_pkg",
        executable ="robot_news",
        name = "My_FM",
        remappings={parameter_rename}
    )
    Robot_News_S5 = Node(
        package ="my_cpp_pkg",
        executable ="robot_news",
        name = "FM_988",
        remappings={parameter_rename}
    )
    
    
   
    smart_phone_node = Node(
        package="my_cpp_pkg",
        executable="smartphone",
        remappings={parameter_rename}


    )
    ld.add_action(Robot_News_S1)
    ld.add_action(Robot_News_S2)
    ld.add_action(Robot_News_S3)
    ld.add_action(Robot_News_S4)
    ld.add_action(Robot_News_S5)
    ld.add_action(smart_phone_node)


    

    return ld