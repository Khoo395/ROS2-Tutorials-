#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/set_bool.hpp"
#include <iostream>
using std::placeholders::_1;


class Service_Client : public rclcpp::Node 
{
public:
    Service_Client() : Node("Number_Reset_Client")
    {
    

    thread1 = std::thread(std::bind(&Service_Client::Call_Service,this));
    }

    void Call_Service ()
    {
        client = this->create_client<example_interfaces::srv::SetBool>("reset_counter"); 
        while (!client->wait_for_service(std::chrono::seconds(1))){
            RCLCPP_WARN(this->get_logger(), "Waiting for the server to be up...");

        }
        RCLCPP_INFO(this->get_logger(),"The Server is Up");
        
        while(true){
        std::cout<< "Please type 1 for reset or 0 for nothing";
        int if_reset_;
        std::cin >> if_reset_;
        RCLCPP_INFO(this->get_logger(),"Input taken");

        auto request = std::make_shared<example_interfaces::srv::SetBool::Request>();
        request->data = if_reset_; 

        auto response = client->async_send_request(request);

        try 
        {
        RCLCPP_INFO(this->get_logger(),response.get()->message);
        }

        catch(const std::exception &e)
        {
        RCLCPP_INFO(this->get_logger(), "Service Call Failed");
        }
        }

    }

private:
std::thread thread1;
rclcpp::Client<example_interfaces::srv::SetBool>::SharedPtr client; 
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Service_Client>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
