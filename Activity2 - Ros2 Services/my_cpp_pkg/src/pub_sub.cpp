#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "example_interfaces/srv/set_bool.hpp"
using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;


class Publisher_Subsriber: public rclcpp::Node
{
public:
    Publisher_Subsriber()
    :Node("Publisher_Subscriber"), count_(0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("number_count",10);
        subscriber_ = this->create_subscription<std_msgs::msg::String>("number", 10, std::bind(&Publisher_Subsriber::TopicCallback, this, _1));
        server = this->create_service<example_interfaces::srv::SetBool>("reset_counter",std::bind(&Publisher_Subsriber::Callback_Reset_Num, this, _1, _2));
        RCLCPP_INFO(this->get_logger(), "Number Counter has been started");
    }


private: 
void TopicCallback(const std_msgs::msg::String::SharedPtr msg)
{
count_++; 
auto message = std_msgs::msg::String();
message.data = count_;
RCLCPP_INFO(this->get_logger(),"I heard %d count: " ,count_);
publisher_->publish(message); 
}

rclcpp::Publisher<std_msgs::msg::String>:: SharedPtr publisher_;  
int count_ = 0; 
rclcpp::Subscription<std_msgs::msg::String>:: SharedPtr subscriber_;
rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server;

void Callback_Reset_Num (example_interfaces::srv::SetBool::Request::SharedPtr request, example_interfaces::srv::SetBool::Response::SharedPtr response)
{

if(request->data){
    count_ = 0;
    response->success = true;
    response->message = "Service Call Success, the counter has been reset";
}
else
{
response->success = false;
response->message = "Service Call Fail, the counter has not been reset.";

}



}







};


int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Publisher_Subsriber>());
    rclcpp::shutdown();

}
