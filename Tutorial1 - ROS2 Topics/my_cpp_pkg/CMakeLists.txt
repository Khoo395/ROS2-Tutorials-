cmake_minimum_required(VERSION 3.5)
project(my_cpp_pkg)

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
find_package(example_interfaces)
find_package(std_msgs)


find_package(std_msgs REQUIRED)
add_executable(node1 src/number_publisher.cpp)
ament_target_dependencies(node1 rclcpp std_msgs)

add_executable(node2 src/pub_sub.cpp)
ament_target_dependencies(node2 rclcpp std_msgs example_interfaces)


install(TARGETS
node1
node2
DESTINATION lib/${PROJECT_NAME}
)






ament_package()

