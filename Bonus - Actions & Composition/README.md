## ROS Actions and Composition
This is a Bonus Section where I explored using Actions and Composition, which is out of the contents of the course I followed.
The program written mimicks the Turtlesim package teleop_key node, which enables user to control turtle via keyboard. 
    

### Actions 
Actions, like messages and services, is a type of interface for communication between nodes. Action Client will send a goal to the action server, which can respond by accepting or rejecting the goal. In addition, a sent goal can be cancelled by the request of the client. The option of a feedback also available during an after a goal executes. Actions are normally used for longer processes that requires more flecibility. More info is available on the Action [Design Page](http://design.ros2.org/articles/actions.html). 

### Composition
Composition is an alternative to Launch services for running multiple nodes in a single terminal. It allows  one to run nodes from static libraries (.so files in Ubuntu) provided valid header files is available. More information can be found [here](https://docs.ros.org/en/foxy/Tutorials/Composition.html). 

<br> </br>
## Steps to Run 
To run this program, clone action_tutorials_cpp to your Ros workspace src folder. Then, enter the code below to build the program. 

```bash
colcon build --packages-select action_tutorials_cpp 
```

After the build is successful, you will need to execute the 2 parts of code below in 2 different terminals. 

**Terminal 1**
```bash
ros2 run action_tutorials_cpp manual_composition2
```

**Terminal 2**
```bash
ros2 run turtlesim turtlesim_node
```


