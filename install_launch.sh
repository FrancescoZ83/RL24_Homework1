#!/bin/bash
colcon build
source install/setup.bash
ros2 launch arm_gazebo arm_world.launch.py
