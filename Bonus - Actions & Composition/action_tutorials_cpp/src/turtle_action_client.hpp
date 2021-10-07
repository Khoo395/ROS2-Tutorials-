#pragma once
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "my_robot_interfaces/action/turtle_move.hpp"

namespace action_tutorials_cpp{
class TurtleActionClient : public rclcpp::Node {
    public:
    using TurtleMove= my_robot_interfaces::action::TurtleMove;
    using GoalHandleTurtleMove = rclcpp_action::ClientGoalHandle<TurtleMove>;
 explicit TurtleActionClient(const rclcpp::NodeOptions & options);

private:
rclcpp_action::Client<TurtleMove>::SharedPtr action_client_; 
GoalHandleTurtleMove::SharedPtr last_goal;

}; 
}
