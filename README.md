# ROS 2 Humble — Tutorials Repository

Personal repository for working through the official
[ROS 2 Humble Tutorials](https://docs.ros.org/en/humble/Tutorials.html). Includes custom packages in
both C++ and Python covering the core ROS 2 concepts.

## Requirements

- Install
    [ROS 2 Humble](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html) on
    Ubuntu 22.04

## Setup

Clone the repository:
```bash
git clone git@github.com:luisluna01/ros_tutorial.git
cd ros_tutorials # Navigate to ROS2 workspace
```

## Build

Source ROS 2, then build and source the ROS2 workspace:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

## Author

Luis Luna
