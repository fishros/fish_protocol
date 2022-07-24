/**
 * @brief 文件描述：待完善
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-24
 * @copyright 版权所有：（鱼香ROS）fishros.org.cn
 */
#ifndef _FISH_PROTOCOL_SERIAL_PROTOCOL_H_
#define _FISH_PROTOCOL_SERIAL_PROTOCOL_H_
#include <unistd.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <string>

#include "fish_protocol/fish_protocol_define.h"

namespace fish_protocol {

class SerialProtocol : public FishProtocol {
 private:
  void _asyncReadSomeData();
  void _initSerialProtocol();
  void _recvDataCallback(const boost::system::error_code& error,
                         size_t bytes_transferred);

 public:
  SerialProtocol(const ProtocolConfig& protocol_config)
      : FishProtocol(protocol_config),
        io_service_(),
        serial_port_(io_service_) {
    _initSerialProtocol();
  }
  int ProtocolSendRawData(const std::string& data) override;
  int ProtocolDestory() override;

 private:
  char recv_data_buffer_[1024]{};
  boost::asio::io_service io_service_;
  boost::asio::serial_port serial_port_;
};
}  // namespace fish_protocol
#endif  // _FISH_PROTOCOL_SERIAL_PROTOCOL_H_
