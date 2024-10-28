#!/bin/bash

colcon build
source install/local_setup.bash
ros2 launch arm_gazebo arm_gazebo.launch.py
