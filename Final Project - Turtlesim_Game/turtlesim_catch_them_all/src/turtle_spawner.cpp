
#include "rclcpp/rclcpp.hpp"
#include <random>
#include <iostream>
#include "my_robot_interfaces/msg/alive_turtles.hpp"
#include "my_robot_interfaces/msg/turtle.hpp"
#include "my_robot_interfaces/srv/kill_turtle_list.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/srv/kill.hpp"
using std::placeholders::_1;
using std::placeholders::_2;


class TurtleSpawner : public rclcpp::Node // MODIFY NAME
{
public:
    TurtleSpawner() : Node("node_name") // MODIFY NAME
    {
        
        publisher = this->create_publisher<my_robot_interfaces::msg::AliveTurtles>("alive_turtles",10);
        timer = this->create_wall_timer(std::chrono::seconds(1),std::bind(&TurtleSpawner::callback_publish,this));
        service = this->create_service<my_robot_interfaces::srv::KillTurtleList>("kill_turtle_list", std::bind(&TurtleSpawner::edit_turtle_list,this,_1,_2));
        spawn_turtle_test();

    }

private:
void edit_turtle_list(my_robot_interfaces::srv::KillTurtleList_Request::SharedPtr request, my_robot_interfaces::srv::KillTurtleList_Response::SharedPtr response){
    int size = turtle_list.turtle_stats.size();
    for(int i =0; i<15; i++){
        if(turtle_list.turtle_stats[i].turtle_id == request->turtle_id)
        {turtle_list.turtle_stats[i] = turtle_list.turtle_stats[size-1];
        turtle_list.turtle_stats.pop_back();
        response->success = true;
        threads.push_back(std::thread(std::bind(&TurtleSpawner::SendKillRequest,this,request)));
        
        }
    }
    RCLCPP_INFO(this->get_logger(),"Turtle %d is removed", request->turtle_id); 


}

void wait(const int& seconds){
int time_now = this->get_clock()->now().seconds();
while((this->get_clock()->now().seconds()- time_now) < seconds){}
}

void spawn_turtle_test()
{
    for(int i =0; i<5; i++){
        wait(1);
        threads.push_back(std::thread(std::bind(&TurtleSpawner::spawn_turtle,this)));
        }
        }

void Spawn_Service(const std::string& turtle_id, double& x_pos, double& y_pos, double& theta)
{
    auto client = this->create_client<turtlesim::srv::Spawn>("spawn");
    while(!client->wait_for_service(std::chrono::seconds(1))){
        RCLCPP_WARN(this->get_logger(), "Waiting for turtlesim node to be up");
    }
    auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
    request->name = "turtle_" + turtle_id;
    request->x = (float)x_pos;
    request->y = (float)y_pos;
    request->theta = (float)theta; 

    auto future = client->async_send_request(request);
    try{
        auto response = future.get();
    }
    catch(const std::exception &e)
    {RCLCPP_ERROR(this->get_logger(),"Spawn Service Failed");}

    auto response = future.get();
    if (response->name == turtle_id)
    {RCLCPP_ERROR(this->get_logger(),"Turtle %s spawned succesfully",response->name);}
}

void SendKillRequest(my_robot_interfaces::srv::KillTurtleList_Request::SharedPtr request_id)
{   
    auto client2 = this->create_client<turtlesim::srv::Kill>("kill");
    while(!client2->wait_for_service(std::chrono::seconds(1)))
    {RCLCPP_WARN(this->get_logger(),"Turtlesim is not Up yet!");}

    auto request = std::make_shared<turtlesim::srv::Kill_Request>();
    request->name = "turtle_" + std::to_string(request_id->turtle_id);
    RCLCPP_WARN(this->get_logger(), request->name);
    auto future = client2->async_send_request(request);
    try
    {
    auto response = future.get();
    RCLCPP_INFO(this->get_logger(),"Turtle_%d updated successfully", request_id->turtle_id);
    }
    catch(const std::exception& e)
    {
        RCLCPP_ERROR(this->get_logger(),"Turtle kill service Failed");
    }
    threads.push_back(std::thread(std::bind(&TurtleSpawner::spawn_turtle,this)));
}


void callback_publish()
{
    publisher->publish(turtle_list);
}

void spawn_turtle()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.25, 10.75);
    std::uniform_real_distribution<double> angle(0.0, 11.0);
    my_robot_interfaces::msg::Turtle turtle_array; 
    turtle_array.turtle_id = unique_id();
    turtle_array.x_pos = dist(mt);
    turtle_array.y_pos = dist(mt);
    turtle_array.theta = angle(mt); 
    turtle_list.turtle_stats.push_back(turtle_array);
    Spawn_Service(std::to_string(turtle_array.turtle_id),turtle_array.x_pos,turtle_array.y_pos, turtle_array.theta);
    
}


 

int unique_id()
{
    int size = turtle_list.turtle_stats.size();
    if (size==0){return 1;}

    for(int i=1; i<16; i++)
    {
    for(int j=0;j<size;j++)
    {
     if( i == turtle_list.turtle_stats[j].turtle_id){break;}   
     if (j == size-1){return i;}
    }

    }
    return 0; 
}
my_robot_interfaces::msg::AliveTurtles turtle_list; 
rclcpp::Publisher<my_robot_interfaces::msg::AliveTurtles>::SharedPtr publisher;
rclcpp::TimerBase::SharedPtr timer;
rclcpp::Service<my_robot_interfaces::srv::KillTurtleList>::SharedPtr service; 
std::vector <std::thread> threads; 

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleSpawner>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
