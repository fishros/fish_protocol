/**
 * @brief 文件描述：待添加
 *        参考代码：https://www.boost.org/doc/libs/1_38_0/doc/html/boost_asio/tutorial/tutdaytime6.html
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-24
 * @copyright 版权所有：（鱼香ROS）fishros.org.cn
 */

#include "fish_protocol/udp_server_protocol.h"

namespace fish_protocol {
void UdpServerProtocol::_initUdpServerProtocol() {
  using boost::asio::ip::address;
  using boost::asio::ip::udp;
  boost::system::error_code ec;
  socket_.open(udp::v4());
  socket_.bind(
      udp::endpoint(address::from_string(protocol_config_.udp_server_ip_),
                    protocol_config_.udp_server_port_));
  _asyncReadSomeData();
  boost::thread td(boost::bind(&boost::asio::io_service::run, &io_service_));
}

void UdpServerProtocol::_recvDataCallback(
    const boost::system::error_code& error, size_t bytes_transferred) {
  if (bytes_transferred > 0) {
    std::string data_str(recv_data_buffer_, bytes_transferred);
    // 回调数据
    // printf("recv data %ld\n", bytes_transferred);
    recv_data_callback_(data_str);
    // printf("%s,%d\n", remote_endpoint_.address().to_v4().to_string().c_str(),
    //        remote_endpoint_.port());
  }
  _asyncReadSomeData();
}

void UdpServerProtocol::_asyncReadSomeData() {
  socket_.async_receive_from(
      boost::asio::buffer(recv_data_buffer_), remote_endpoint_,
      boost::bind(&UdpServerProtocol::_recvDataCallback, this,
                  boost::placeholders::_1, boost::placeholders::_2));
}

int UdpServerProtocol::ProtocolSendRawData(const std::string& data) {
  std::cout << "send" << data.size() << std::endl;
  print_frame_to_hex("send", data.data(), data.size());
  if (remote_endpoint_.port() != 0) {
    int send_len = socket_.send_to(boost::asio::buffer(data), remote_endpoint_);
    return send_len;
  }
  return -1;
}

int UdpServerProtocol::ProtocolDestory() {
  io_service_.stop();
  return 0;
}

}  // namespace fish_protocol
