## ROS Topics
This tutorial implements basic Subscriber and Publisher in Ros2.

 Node 1 has a subscriber which is publishing a
 constant value to the "number" topic.
Node2, having both a publisher and a subscriber, listens for data published to topic "number", and publishes an inreasing counter to the topic "number counter" for each count received. 