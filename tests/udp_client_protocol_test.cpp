/**
 * @brief 文件描述：UDPServer协议测试
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-17
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fish_protocol/fish_protocol.h"
#include "gtest/gtest.h"

using boost::asio::ip::address;
using boost::asio::ip::udp;


TEST(TestUdpClientProtocol, ReadData) {
  using namespace fish_protocol;  // NOLINT
  ProtocolConfig proto_config;
  proto_config.protocol_type_ = PROTOCOL_TYPE::UDP_CLIENT;
  proto_config.udp_server_ip_ = "192.168.4.1";
  proto_config.udp_server_port_ = 3474;

  auto protocol = fish_protocol::GetProtocolByConfig(proto_config);

  std::string send_data("\x5A\x01\x02\x51\x02\x50\x01\x5A");
  protocol->ProtocolSendRawData(send_data);

  protocol->SetDataRecvCallback([send_data](const std::string& data) -> void {
    print_frame_to_hex("recvframe", data.data(), (uint16_t)data.size());
    EXPECT_STREQ(send_data.data(), data.data());
  });

  /*
    关于Lambda:
    - [ capture ] ( params ) opt -> ret { body; };
    - 其中 capture 是捕获列表，params 是参数表，opt 是函数选项，ret
    是返回值类型，body是函数体
  */
  sleep(20);
  protocol->ProtocolDestory();
}
