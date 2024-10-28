From the ./ros2_ws folder of the Docker container of the class.

1) Run "./src/install_gazebo.sh" and check that in Gazebo and on terminal all is working properly.
2) On a second terminal, connect to the existing container and run "./src/launch_rviz.sh". Check that the URDF of the robot is correct and the camera is working

Now, you can close Gazebo and Rviz. Check that the arm_controller_node publisher and subscriber work properly.

Use "./src/launch_node.sh" to run the node. You can check on the second terminal the active topics with "ros2 topic list".

On the second terminal, test the publisher with the command "ros2 topic echo /position_controller/command" and see that the command position of the joint are being published.

Always on the second terminal, test the subscriber by manually publishing to the topic:

ros2 topic pub /joint_states sensor_msgs/msg/JointState "{name: ['j0', 'j1', 'j2', 'j3'], position: [2.0, 0.8, -0.1, 0.5]}"
