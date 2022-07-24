/**
 * @brief 文件描述：待完善
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-24
 * @copyright 版权所有：（鱼香ROS）fishros.org.cn
 */
#ifndef _FISH_PROTOCOL_FISH_PROTOCOL_DEFINE_H_
#define _FISH_PROTOCOL_FISH_PROTOCOL_DEFINE_H_
#include <functional>
#include <iostream>
#include <string>
#include <memory>

#include "fish_protocol/protocol_util.h"

namespace fish_protocol {
enum class PROTOCOL_TYPE : int {
  SERIAL = 0,
  UDP_SERVER,
  TCP_SERVER,
};

class ProtocolConfig {
 public:
  PROTOCOL_TYPE protocol_type_;
  // serial
  int serial_baut_;
  std::string serial_address_;
  // udp
  int udp_server_port_;
  std::string udp_server_ip_;
  // tcp
  int tcp_server_port_;
  std::string tcp_server_ip_;

  ProtocolConfig& operator=(const ProtocolConfig& config) {
    protocol_type_ = config.protocol_type_;
    serial_baut_ = config.serial_baut_;
    serial_address_ = config.serial_address_;
    udp_server_ip_ = config.udp_server_ip_;
    udp_server_port_ = config.udp_server_port_;
    tcp_server_ip_ = config.tcp_server_ip_;
    tcp_server_port_ = config.tcp_server_port_;
    return *this;
  };

 public:
  ProtocolConfig() = default;
  ~ProtocolConfig() = default;
};

class FishProtocol {
 protected:
  std::function<void(const std::string&)> recv_data_callback_;
  ProtocolConfig protocol_config_;

 public:
  FishProtocol(const ProtocolConfig& protocol_config);
  ~FishProtocol() = default;

 public:
  virtual int ProtocolSendRawData(const std::string& data) = 0;
  virtual int ProtocolDestory() = 0;
  void SetDataRecvCallback(std::function<void(const std::string&)> callback);
};



}  // namespace fish_protocol
#endif  // _FISH_PROTOCOL_FISH_PROTOCOL_DEFINE_H_