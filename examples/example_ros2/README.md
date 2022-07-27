# ROS2使用方法例程

1.创建功能包

```
ros2 pkg create example_fish_protocol --dependencies rclcpp fish_deploy --node-name example_fish_protocol --maintainer-name fishros
```

2.编译

```
colcon build
```

3.执行

```
ros2 run example_fish_protocol example_fish_protocol
```