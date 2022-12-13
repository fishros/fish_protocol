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

  /* 运行节点，并检测退出信号 Ctrl+C*/
  rclcpp::spin(node);
  
  // 销毁
  protocol->ProtocolDestory();
  /* 停止运行 */
  rclcpp::shutdown();
  return 0;
}
