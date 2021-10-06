## ROS Services 
This activity is an extension to Activity 1. ROS service is implemented to enable the function of  resetting the counter.  


To acheive this, a new node "Service Client" is created, and has the ability to send a request to the server node. 

A Server  is also initiated in "pub_sub.cpp". On receiving a request, it accepts it and call the related function to reset the counter. 

<br> </br>
## Steps to Run 
To run this program, clone the my_cpp_pkg to your Ros workspace src folder. Then, enter the code below to build the program. 

```bash
colcon build --packages-select my_cpp_pkg 
```

After the build is successful, you will need to execute the three parts of code below in 3 different terminals.

**Terminal 1**
```bash
ros2 run my_cpp_pkg node1
```

**Terminal 2**
```bash
ros2 run my_cpp_pkg node2
```

**Terminal 3**
```bash
ros2 run my_cpp_pkg node3
```