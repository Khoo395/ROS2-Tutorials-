#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"
#include "my_robot_interfaces/msg/led_state.hpp"
using std::placeholders::_1;
using std::placeholders::_2;


class LedNode : public rclcpp::Node // MODIFY NAME
{
public:
    LedNode() : Node("set_led") // MODIFY NAME
    {
        publisher = this->create_publisher<my_robot_interfaces::msg::LedState>("led_states",10);
        this -> declare_parameter("led_states", std::vector<int64_t>{0, 0, 1});

        LedState.led_state = this->get_parameter("led_states").as_integer_array();
        if(LedState.led_state[1] == 0){
        RCLCPP_INFO(this->get_logger(), "abc %d", LedState.led_state[1]);
        }
        
        timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&LedNode::PublishLedState, this ));
        server = this->create_service<my_robot_interfaces::srv::SetLed>("set_led", std::bind(&LedNode::setLed, this, _1,_2));

    }

private:

void PublishLedState()
{
publisher->publish(LedState);
}

void setLed(my_robot_interfaces::srv::SetLed::Request::SharedPtr request, my_robot_interfaces::srv::SetLed::Response::SharedPtr response)
{
LedState.led_state[request->led_number] = request->state;
if(request->state == 1)
{
RCLCPP_INFO(this->get_logger(), "LED %d turned on", request->led_number);
}
else{RCLCPP_INFO(this->get_logger(), "LED %d turned off", request->led_number);}
response->success = true;
}
rclcpp::Service<my_robot_interfaces::srv::SetLed>::SharedPtr server; 
rclcpp::Publisher<my_robot_interfaces::msg::LedState>::SharedPtr publisher; 
rclcpp::TimerBase::SharedPtr timer; 
my_robot_interfaces::msg::LedState LedState; 

};





int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LedNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
