#pragma once
#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/action/turtle_move.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"


namespace action_tutorials_cpp{
class TurtleActionServer: public rclcpp::Node {
    public:
    using TurtleMove= my_robot_interfaces::action::TurtleMove;
    using GoalHandleTurtleMove = rclcpp_action::ServerGoalHandle<TurtleMove>;
    explicit TurtleActionServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());


private:
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher; 
rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber; 
std::array<double,2> turtle_position;
rclcpp_action::Server<TurtleMove>::SharedPtr action_server_; 
};
}