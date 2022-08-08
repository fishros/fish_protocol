/**
 * @brief 文件描述：待完善
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-24
 * @copyright 版权所有：（鱼香ROS）fishros.org.cn
 */
#ifndef _FISH_PROTOCOL_FISH_PROTOCOL_H_
#define _FISH_PROTOCOL_FISH_PROTOCOL_H_
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/thread.hpp>
#include <functional>
#include <iostream>
#include <string>

#include "fish_protocol/serial_protocol.h"
#include "fish_protocol/udp_server_protocol.h"
#include "fish_protocol/udp_client_protocol.h"

namespace fish_protocol {
std::shared_ptr<FishProtocol> GetProtocolByConfig(
    const ProtocolConfig& protocol_config);

}
#endif  // _FISH_PROTOCOL_FISH_PROTOCOL_H_