#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/msg/robot_name.hpp"
using std::placeholders::_1;


class SmartPhoneNode : public rclcpp::Node // MODIFY NAME
{
public:
    SmartPhoneNode() : Node("Smart_Phone") // MODIFY NAME
    {
        subscriber = this->create_subscription<my_robot_interfaces::msg::RobotName>("Robot_Name",10,std::bind(&SmartPhoneNode::Callback, this, _1));
    }

private:
void Callback(my_robot_interfaces::msg::RobotName::SharedPtr name)
{
RCLCPP_INFO(this->get_logger(), "I hear Robot %s", name->robot_name.c_str());
}
rclcpp::Subscription<my_robot_interfaces::msg::RobotName>::SharedPtr subscriber; 
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartPhoneNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
    
}

