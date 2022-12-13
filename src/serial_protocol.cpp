/**
 * @brief 文件描述：待完善
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-24
 * @copyright 版权所有：（鱼香ROS）fishros.org.cn
 */
#include "fish_protocol/serial_protocol.h"

namespace fish_protocol
{
  void SerialProtocol::_initSerialProtocol()
  {
    boost::system::error_code ec;
    std::cout << "open with" << protocol_config_.serial_address_ << std::endl;
    serial_port_.open(protocol_config_.serial_address_, ec);
    assert(!ec);
    serial_port_.set_option(
        boost::asio::serial_port_base::baud_rate(protocol_config_.serial_baut_));
    serial_port_.set_option(boost::asio::serial_port_base::character_size(8));
    serial_port_.set_option(boost::asio::serial_port_base::stop_bits(
        boost::asio::serial_port_base::stop_bits::one));
    serial_port_.set_option(boost::asio::serial_port_base::parity(
        boost::asio::serial_port_base::parity::none));
    serial_port_.set_option(boost::asio::serial_port_base::flow_control(
        boost::asio::serial_port_base::flow_control::none));
    _asyncReadSomeData();
    boost::thread td(boost::bind(&boost::asio::io_service::run, &io_service_));
  }

  void SerialProtocol::_recvDataCallback(const boost::system::error_code &error,
                                         size_t bytes_transferred)
  {
    if (bytes_transferred > 0)
    {
      std::string data_str(recv_data_buffer_, bytes_transferred);
      if (recv_data_callback_)
      {
        // 回调数据
        recv_data_callback_(data_str);
      }
    }
    _asyncReadSomeData();
  }

  void SerialProtocol::_asyncReadSomeData()
  {
    serial_port_.async_read_some(
        boost::asio::buffer(recv_data_buffer_, sizeof(recv_data_buffer_)),
        boost::bind(&SerialProtocol::_recvDataCallback, this,
                    boost::placeholders::_1, boost::placeholders::_2));
  }

  int SerialProtocol::ProtocolSendRawData(const std::string &data)
  {
    std::cout << "send" << data.size() << std::endl;
    print_frame_to_hex("send", data.data(), data.size());
    serial_port_.write_some(boost::asio::buffer(data.data(), data.size()));
    return 0;
  }

  int SerialProtocol::ProtocolDestory()
  {
    io_service_.stop();
    serial_port_.cancel();
    serial_port_.close();
    return 0;
  }

} // namespace fish_protocol
