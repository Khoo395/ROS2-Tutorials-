## ROS Topics
This tutorial implements basic Subscriber and Publisher in Ros2.

 Node 1 has a subscriber which is publishing a
 constant value to the "number" topic.
Node2, having both a publisher and a subscriber, listens for data published to topic "number", and publishes an inreasing counter to the topic "number counter" for each count received. 

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