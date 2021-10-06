#include "rclcpp/rclcpp.hpp"
#include "my_robot_interfaces/srv/set_led.hpp"

class BatteryNode : public rclcpp::Node // MODIFY NAME
{
public:

    BatteryNode() : Node("Battery") // MODIFY NAME
    {
        RCLCPP_WARN(this->get_logger(),"The Battery is Fully Charged!");
        thread1 = std::thread(std::bind(&BatteryNode::Alter_Battery_State, this));
        battery_timer = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&BatteryNode::Check_Battery_State,this));
        
        
    }




    void Check_Battery_State()
    {
        if(previous_battery_state_ != battery_state_)
        { 
            if (previous_battery_state_ == 0)
            {
                RCLCPP_WARN(this->get_logger(),"The Battery is Fully Charged!");
            }

            else
            {
                RCLCPP_WARN(this->get_logger(),"The Battery ran out!");
            }
            threads.push_back(std::thread(std::bind(&BatteryNode::Control_Led,this,battery_state_,2)));
            previous_battery_state_ = battery_state_;
        }

    }

    void Alter_Battery_State()
    {while(true)
    {   time_now = this->get_clock()->now().seconds();
        while((this->get_clock()->now().seconds() - time_now) < 4)
        {
            

        }
        this->battery_state_ = !battery_state_;
        time_now = this->get_clock()->now().seconds();
        while((this->get_clock()->now().seconds() - time_now) < 6)
        {
            

        }
        this->battery_state_ = !battery_state_;
        
    }

    }

    void Control_Led(bool battery_state, int led_num)
    {
        bool led_state = !battery_state; // LED will be on when no battery, and vice versa. 
        auto client = this->create_client<my_robot_interfaces::srv::SetLed>("set_led");
        while(!client->wait_for_service(std::chrono::seconds(1)) )
        {
            RCLCPP_WARN(this->get_logger(), "Waiting the server to be up...");

        }
        auto request = std::make_shared<my_robot_interfaces::srv::SetLed::Request>();
        request->led_number = led_num;
        request->state = led_state;
        auto future = client->async_send_request(request);

        try 
        {
        auto response = future.get();
        if (response->success == 1)
        {
            RCLCPP_INFO(this->get_logger(), "Led state changed :)");
        }

        else
        {
            RCLCPP_INFO(this->get_logger(), "Led state unchanged :(");
        }
        }

        catch(const std::exception &e)
        {
        RCLCPP_INFO(this->get_logger(), "Service Call Failed");
        }

    }

private:
bool battery_state_ = 1;
bool previous_battery_state_ = 1;
bool update_ = 0;
double time_now;
rclcpp::TimerBase::SharedPtr battery_timer;
std::vector<std::thread> threads; 
std::thread thread1;

};



int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BatteryNode>();
    rclcpp::spin(node);
    return 0;
}
