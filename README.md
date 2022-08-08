# FishProtocol 

FishProtocol是一个方便的C++多协议(串口/UDP/TCP)通信库。

FishProtocol是从FishBot的Driver中抽离出的，采用boost库作为核心进行了二次封装，可以简单快速的通过几行代码建立串口/UDP等通信。随着FishBot的不断完善，该库也将不断的更新完善，后续将同时支持对多端进行同时连接，实现多机控制等功能。

同时该库也可以在ROS2中使用，工程中提供有相关例程，见examples文件夹。

## 快速安装

```
sudo apt install libboost-dev
git clone https://gh.api.99988866.xyz/https://github.com/fishros/fish_protocol.git 
cd fish_protocol && mkdir build  && cd build
cmake .. && sudo make install # 将安装到系统库
```

## 快速使用/串口通信

```cpp
fish_protocol::ProtocolConfig proto_config;
proto_config.protocol_type_ = PROTOCOL_TYPE::SERIAL;
proto_config.serial_baut_ = 115200;
proto_config.serial_address_ = "/dev/ttyS12";

// 初始化
auto protocol = GetProtocolByConfig(proto_config);

// 发送数据
protocol->ProtocolSendRawData("Hello FishBot!");

// 接收数据
protocol->SetDataRecvCallback([](const std::string& data) -> void {
    std::cout<<"recv"<<data<<std:endl;
});

// 销毁
protocol->ProtocolDestory();
```

## 快速上手/UDPServer通信

```cpp
fish_protocol::ProtocolConfig proto_config;
proto_config.protocol_type_ = PROTOCOL_TYPE::UDP_SERVER;
proto_config.udp_server_ip_ = "0.0.0.0";
proto_config.udp_server_port_ = 3474;

// 初始化
auto protocol = GetProtocolByConfig(proto_config);

// 发送数据
protocol->ProtocolSendRawData("Hello FishBot!");

// 接收数据
protocol->SetDataRecvCallback([](const std::string& data) -> void {
    std::cout<<"recv"<<data<<std:endl;
});

// 销毁
protocol->ProtocolDestory();
```

## 在ROS2中使用-串口通信

```cpp
#include "fish_protocol/fish_protocol.h"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char** argv) {
  /* 初始化rclcpp  */
  rclcpp::init(argc, argv);
  /*产生一个node_01的节点*/
  auto node = std::make_shared<rclcpp::Node>("example_fish_protocol");
  // 打印一句自我介绍
  RCLCPP_INFO(node->get_logger(), "example_fish_protocol节点已经启动.");

  fish_protocol::ProtocolConfig proto_config;
  proto_config.protocol_type_ = fish_protocol::PROTOCOL_TYPE::SERIAL;
  proto_config.serial_baut_ = 115200;
  proto_config.serial_address_ = "/dev/ttyS12";
  // 初始化
  auto protocol = GetProtocolByConfig(proto_config);
  // 发送数据
  protocol->ProtocolSendRawData("Hello FishBot!");
  // 接收数据
  protocol->SetDataRecvCallback([](const std::string& data) -> void {
    std::cout << "recv" << data << std::endl;
  });
  // 销毁
  protocol->ProtocolDestory();

  /* 运行节点，并检测退出信号 Ctrl+C*/
  rclcpp::spin(node);
  /* 停止运行 */
  rclcpp::shutdown();
  return 0;
}

```


## 常见错误与解决方法

1. can't open shared object file: No such file or direction

```
sudo sh -c "echo '/usr/local/lib' >> /etc/ld.so.conf"
sudo ldconfig
```

## 更新日志

- *20220807*
  添加UDPCLIENT协议支持

