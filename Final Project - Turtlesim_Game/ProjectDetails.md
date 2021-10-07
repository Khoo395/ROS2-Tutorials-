## Turtlsim Game Project Details 
There are 3 ROS nodes involved in this program, and their relationship is shown in the diagram below. 

![0001](https://user-images.githubusercontent.com/74847078/136343500-8e659ec7-40c2-41d4-b546-a211b154ca9a.jpg)

### turtlesim_node
Graphics part of the program, comes with ROS installation. Request to move, kill, or get information on turtles will ultimately go through here. The components used include:
1. **Publisher to topic turtle1/pose**, which updates position of the catcher data.
2. **Subscriber to topic "turtle1/cmd_vel"**, which is a channel to control catcher turtle speed ad direction 
3. **Service "kill"**, which kills turtle of the name provided.

### spawner 
In charge of spawning  turtles and maintaining a list of spawned turtles position. It also pass over kill requests from controller to turtlesim_node while updating the list. The components used include:
1. **Publisher to topic active_turtles**, which is a list of existing turtles.
2. **Service "kill_turtle_list"**, which pass over the kill request from controller to service "kill" and updates the list.
3. **Service client""kill**, which send request to turtlesim_node to kill a turtle 

### spawner 
In charge of controlling the catcher turtle to catch a random turtle. The components used include:
1. **Subscriber to topic active_turtle1/pose**, to get the position of catcher turtle.
2. **Publisher to  "turtle1/cmd_vel"**, to control the turtle to a desired orientation and speed. 
3. **Service client ""kill_turtle_list**, which send request to spawner to remove a turtle from the list once a turtle is caught. 
