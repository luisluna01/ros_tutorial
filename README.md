# ROS 2 Humble — Tutorials Repository

Personal repository for working through the official [ROS 2 Humble Tutorials](https://docs.ros.org/en/humble/Tutorials.html). Includes custom packages in both C++ and Python covering the core ROS 2 concepts.

## Requirements

- **With Docker** — See the [`docker_ros`](https://github.com/luisluna01/docker_ros) submodule for setup instructions. Only supports machines with an Nvidia GPU.
- **Without Docker** — Install [ROS 2 Humble](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html) on Ubuntu 22.04.

## Setup

Clone the repository with submodules:
```bash
git clone --recurse-submodules git@github.com:luisluna01/ros_tutorial.git
cd ros_tutorials
```

## Docker

This project can run with or without a docker container. The `docker_ros` submodule provides a ready-to-use ROS 2 Humble container. See the `docker_ros` [README.md](docker_ros/README.md) for full instructions.

To launch a container and enter a shell:
```bash
cd docker_ros
docker compose build # Build the docker image
docker compose up -d # Launch the docker container
docker exec -ti ros2_c bash # Open a shell in the container
```

To close the container, exit by pressing `CTL+D` and use the following command:
```bash
cd ..
docker compose down
```

## Build

Source ROS 2, then build with colcon from the workspace root:

```bash
source /opt/ros/humble/setup.bash
colcon build
source install/setup.bash
```

## Author

Luis Luna
