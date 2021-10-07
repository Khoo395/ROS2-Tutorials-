## ROS Interfaces
This is the final project to apply the knowledge learnt in the course. The aim is to build a "game" using the turtlesim interface where a program controlled **Catcher Turtle** will be catching other turtles which are randomly spawned around the map. 


https://user-images.githubusercontent.com/74847078/136246067-1c4c55f8-ec40-43ca-9aa8-f3b0c865fc92.mp4



<br> </br>
## Steps to Run 
To run this program, clone turtlesim_catch_them_all and my_robot_bringup to your Ros workspace src folder. Make sure you have turtlesim installed properly. Then, navigate to your workspace root and enter the code below to build the programs. 

```bash
colcon build --packages-select turtlesim_catch_them_all
colcon build --packages-select my_robot_bringup
```

After the build is successful, you can launch the whole program in 1 terminal with a launch file. Alternatively,  you can also call the 3 programs seperately in 3 terminals. 

### Preffered Way
```bash
ros2 launch my_robot_bringup catch_them_all.launch.py
```

**Alternative Way**

**Terminal 1**
```bash
ros2 run turtlesim turtlesim_node
```

**Terminal 2**
```bash
ros2 run turtlesim_catch_them_all controller
```

**Terminal 2**
```bash
ros2 run turtlesim_catch_them_all spawner
```
