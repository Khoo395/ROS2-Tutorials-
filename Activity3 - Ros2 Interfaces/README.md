## ROS Interfaces
In ROS, messages published to topics and service type used has to be pre-defined. Most of the types can be found from the std_msgs and example_interfaces library. User can also choose to self define their msg/srv type.  

In this activity, I created user defined interfaces including message(for topic) and service to be used in a battery state led program. 

The battery node will go through charge and recharge phase (simulated by constant time period), and will send out service request to the led node to switch the leds. The Led node will also constantly publish its state to another topic.

<br> </br>
## Steps to Run 
To run this program, clone my_cpp_pkg and my_robot interfaces to your Ros workspace src folder. Then, enter the code below to build the program. 

```bash
colcon build --packages-select my_cpp_pkg 
colcon build --packages-select my_robot_interfaces 
```

After the build is successful, you will need to execute the 2 parts of code below in 2 different terminals. A third terminal can be used to observe the msg published by led node.

**Terminal 1**
```bash
ros2 run my_cpp_pkg battery
```

**Terminal 2**
```bash
ros2 run my_cpp_pkg led
```

**Terminal 3**(Optional)
```bash
ros2 topic echo /led_states
```