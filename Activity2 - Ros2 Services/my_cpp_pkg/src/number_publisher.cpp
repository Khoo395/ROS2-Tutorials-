#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using namespace std::chrono_literals;


class number_Publisher : public rclcpp::Node
{
public:
    number_Publisher()
    :Node("number_publisher")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("number",10);
        timer_ = this->create_wall_timer(500ms, std::bind(&number_Publisher::TimerCallback,this));

    }

private: 
void TimerCallback()
{
auto message = std_msgs::msg::String();
message.data = std::to_string(73);
RCLCPP_INFO(this->get_logger(), "Publishing '%s'", message.data.c_str());
publisher_-> publish(message); 
}

rclcpp::TimerBase::SharedPtr timer_; 
rclcpp::Publisher<std_msgs::msg::String>:: SharedPtr publisher_;  
};



int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<number_Publisher>());
    rclcpp::shutdown();

}