# Creating a launch file
The launch file created in this directory is from [this](https://docs.ros.org/en/humble/Tutorials/Intermediate/Launch/Creating-Launch-Files.html) tutorial.

In order to use the launch file, first navigate to this directory:
```bash
cd ../ros_tutorials/src/launch_tutorial/creating_launch_file/
```

Then run the following command:
```bash
ros2 launch turtlesim_mimic_launch.py
```

To test the executables launched, run the following command:
```bash
ros2 topic pub -r 1 /turtlesim1/turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: -1.8}}"
```