# ROS2使用方法例程

1.创建功能包

```
ros2 pkg create example_fish_protocol --dependencies rclcpp fish_deploy --node-name example_fish_protocol --maintainer-name fishros
```

2.编译

```
g++ example_serial.cpp -o example_serial -lfish_protocol -lpthread
```

3.执行

```
./example_serial
```