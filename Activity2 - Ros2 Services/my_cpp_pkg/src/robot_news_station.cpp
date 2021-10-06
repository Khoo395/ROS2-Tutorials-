#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/robot_name.hpp"

class RobotNode : public rclcpp::Node // MODIFY NAME
{
public:
    RobotNode() : Node("Robot_A") // MODIFY NAME
    {
        this->declare_parameter("Robot_Name_Param", "Walley");
        robot_name.robot_name = this->get_parameter("Robot_Name_Param").as_string(); 
        publisher = this->create_publisher<my_robot_interfaces::msg::RobotName>("Robot_Name",10);
        timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&RobotNode::Callback,this));
    }

private:
void Callback()
{
    publisher->publish(robot_name);

}
rclcpp::Publisher<my_robot_interfaces::msg::RobotName>::SharedPtr publisher; 
rclcpp::TimerBase::SharedPtr timer; 
my_robot_interfaces::msg::RobotName robot_name; 

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}