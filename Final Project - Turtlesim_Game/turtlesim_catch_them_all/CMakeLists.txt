cmake_minimum_required(VERSION 3.5)
project(turtlesim_catch_them_all)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(my_robot_interfaces REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(spawner src/turtle_spawner.cpp)
ament_target_dependencies(spawner rclcpp my_robot_interfaces turtlesim)

add_executable(test1 src/controller_test.cpp)
ament_target_dependencies(test1 rclcpp my_robot_interfaces turtlesim)


add_executable(controller src/turtle_controller.cpp)
ament_target_dependencies(controller rclcpp my_robot_interfaces turtlesim geometry_msgs)

add_executable(action_server src/turtle_action_server.cpp)
ament_target_dependencies(action_server rclcpp my_robot_interfaces turtlesim geometry_msgs rclcpp_action)

add_executable(action_client src/turtle_action_client.cpp)
ament_target_dependencies(action_client rclcpp my_robot_interfaces turtlesim rclcpp_action)

install(TARGETS
spawner
controller
test1
action_server
action_client

DESTINATION lib/${PROJECT_NAME}
)



ament_package()
