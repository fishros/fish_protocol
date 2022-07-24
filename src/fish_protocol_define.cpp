/**
 * @brief 文件描述：协议处理工具，打印、crc、转义与反转义
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-24
 * @copyright 版权所有：FishBot Open Source Organization
 */
#include "fish_protocol/fish_protocol_define.h"

namespace fish_protocol {

FishProtocol::FishProtocol(const ProtocolConfig& protocol_config) {
  protocol_config_ = protocol_config;
}

void FishProtocol::SetDataRecvCallback(
    std::function<void(const std::string&)> callback) {
  recv_data_callback_ = callback;
}


}  // namespace fish_protocol
