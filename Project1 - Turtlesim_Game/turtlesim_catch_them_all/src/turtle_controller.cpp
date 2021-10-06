#include "rclcpp/rclcpp.hpp"
#include <random>
#include <iostream>
#include "my_robot_interfaces/msg/alive_turtles.hpp"
#include "my_robot_interfaces/msg/turtle.hpp"
#include "my_robot_interfaces/srv/kill_turtle_list.hpp"
#include "turtlesim/srv/spawn.hpp"
#include "turtlesim/msg/pose.hpp"

#include <cmath>
#include "geometry_msgs/msg/twist.hpp"
using std::placeholders::_1;


class TurtleContoller : public rclcpp::Node 
{
public:
    TurtleContoller() : Node("turtle_controller") 
    {
        list_subscriber = this->create_subscription<my_robot_interfaces::msg::AliveTurtles>("alive_turtles", 10, std::bind(&TurtleContoller::UpdateTurtleList, this, _1)); 
        turtle_pose_subscriber = this->create_subscription<turtlesim::msg::Pose>("turtle1/pose", 10, std::bind(&TurtleContoller::move_turtle, this, _1)); 
        vel_publisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel",10);
        threads.push_back(std::thread(std::bind(&TurtleContoller::SelectTargetTurtle,this)));
        threads.push_back(std::thread(std::bind(&TurtleContoller::control_loop,this)));

       
        
         
        
        //threads.push_back(std::thread(std::bind(&TurtleContoller::SendKillListRequest,this)));

    }


private:
void control_loop(){
    while(true){
        if(turtle_caught){
            SendKillListRequest();
            SelectTargetTurtle();
            turtle_caught = false; 
        }
    }
}



void move_turtle(const turtlesim::msg::Pose::SharedPtr turtle_pose)
{if(target_selected){

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> noise1(-2,2);
    double lvel_noise = noise1(mt);
    double avel_noise = noise1(mt);

    geometry_msgs::msg::Twist vel;
    double target_angle = AngleBetween(turtle_pose->x, turtle_pose->y, target_pose.x, target_pose.y);
    double distance = sqrt(pow((turtle_pose->x - target_pose.x),2) + pow((turtle_pose->y - target_pose.y),2));
    RCLCPP_INFO(this->get_logger(), "The distance is %f", distance); 
    RCLCPP_INFO(this->get_logger(), "The target angle is %f", target_angle ); 
    double avel = SpinDirection(turtle_pose, target_angle);
    avel *= 6; 
    if (distance < 0.3){
    vel.linear.x = 0;
    vel.angular.z = 0;
    RCLCPP_INFO(this->get_logger(), "Turtle %d Captured", target_id); 
    turtle_caught = true; 
    target_selected = false; 
    }
    else if(abs(turtle_pose->theta - target_angle ) < 0.1 || abs(turtle_pose->theta - target_angle)>(2*M_PI - 0.1))
    {
    vel.linear.x = 5 + lvel_noise; 
    vel.angular.z = 0;  
    }
    else if(turtle_pose->x < 0.25 && abs(turtle_pose->theta)> 0.75*M_PI)
    {vel.linear.x = 0; 
    vel.angular.z = avel;}
    else if(turtle_pose->x > 10.75 && abs(turtle_pose->theta)< 0.25*M_PI)
    {vel.linear.x = 0; 
    vel.angular.z = avel;}
    else if(turtle_pose->y < 0.25 && (abs(turtle_pose->theta)> -0.75*M_PI||abs(turtle_pose->theta)< -0.25*M_PI))
    {vel.linear.x = 0; 
    vel.angular.z = avel;}
    else if(turtle_pose->y > 10.25 && (abs(turtle_pose->theta)> 0.25*M_PI||abs(turtle_pose->theta)< 0.75*M_PI))
    {vel.linear.x = 0; 
    vel.angular.z = avel;}


    else{vel.linear.x = 5 + lvel_noise; 
    vel.angular.z = avel + avel_noise; }
    vel_publisher->publish(vel);
}
}

double SpinDirection(const turtlesim::msg::Pose::SharedPtr turtle_pose, double target_angle)
{
    double avel; 
    double A1 ;
    double A2 ;
    if (turtle_pose->theta<0){A1 = turtle_pose->theta + 2*M_PI;}
    else{A1 = turtle_pose->theta;}
    if (target_angle<0){A2 = target_angle + 2*M_PI;}
    else{A2 = target_angle;}
    double diference = A1-A2; 
    if(abs(diference)< M_PI)
    { if(diference>0){avel = -1;}
      else{avel=1; }
    }
    else{
        if(abs(diference)< M_PI)
    { if(diference>0){avel = 1;}
      else{avel=-1; }
    }
    else avel = 1; 

    }


    return avel; 
}


double AngleBetween(const double& turtle_x, const double& turtle_y, const double& target_x, const double& target_y)
{
    double x_distance = target_x - turtle_x;
    double y_distance = target_y - turtle_y;
    double theta = atan2(y_distance,x_distance);
    return theta;
}

void UpdateTurtleList(const my_robot_interfaces::msg::AliveTurtles::SharedPtr new_list)
{turtle_list.turtle_stats = new_list->turtle_stats; 
RCLCPP_INFO(this->get_logger(),"There are %d active turtles", turtle_list.turtle_stats.size());
}

void SendKillListRequest()
{   
    auto client1 = this->create_client<my_robot_interfaces::srv::KillTurtleList>("kill_turtle_list");
    while(!client1->wait_for_service(std::chrono::seconds(1)))
    {RCLCPP_WARN(this->get_logger(),"Spawner is not Up yet!");}

    auto request = std::make_shared<my_robot_interfaces::srv::KillTurtleList_Request>();
    request->turtle_id = target_id;
    auto future = client1->async_send_request(request);
    try
    {
    auto response = future.get();
    if(response->success==true)
    {
        RCLCPP_INFO(this->get_logger(),"Turtle list updated successfully");}  
    }
    catch(const std::exception& e)
    {
        RCLCPP_ERROR(this->get_logger(),"Turtle list updated Failed");
    }
    
}



void wait(const int& seconds){
int time_now = this->get_clock()->now().seconds();
while((this->get_clock()->now().seconds()- time_now) < seconds){}
}


void SelectTargetTurtle()
{   while(turtle_list.turtle_stats.size() ==0){
    wait(1); 
        RCLCPP_WARN(this->get_logger(),"No available Turtle");
    }
    
    int size = turtle_list.turtle_stats.size();
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, (size-1));
    int number = dist(mt);
    RCLCPP_WARN(this->get_logger(),"%d available Turtle",size); 
    target_id = turtle_list.turtle_stats[number].turtle_id;
    target_pose.x = turtle_list.turtle_stats[number].x_pos;
    target_pose.y = turtle_list.turtle_stats[number].y_pos;
    RCLCPP_INFO(this->get_logger(),"Turtle selected %d", target_id);
    target_selected = true; 
    
}


bool target_selected; 
turtlesim::msg::Pose target_pose; 
my_robot_interfaces::msg::AliveTurtles turtle_list;
rclcpp::Subscription<my_robot_interfaces::msg::AliveTurtles>::SharedPtr list_subscriber; 
rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr turtle_pose_subscriber; 
std::vector<std::thread> threads; 
int target_id = 0;
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_publisher;
bool turtle_caught; 


};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleContoller>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
    
}
