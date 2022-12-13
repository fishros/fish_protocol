#include "fish_protocol/fish_protocol.h"

int main(int argc, char const* argv[]) {
  fish_protocol::ProtocolConfig proto_config;
  proto_config.protocol_type_ = fish_protocol::PROTOCOL_TYPE::SERIAL;
  proto_config.serial_baut_ = 115200;
  proto_config.serial_address_ = "/dev/ttyUSB0";

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
  return 0;
}
