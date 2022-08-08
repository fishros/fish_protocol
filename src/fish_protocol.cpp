/**
 * @brief 文件描述：待添加
 *        参考代码：https://www.boost.org/doc/libs/1_38_0/doc/html/boost_asio/tutorial/tutdaytime6.html
 * @author 小鱼 (fishros@foxmail.com)
 * @version V1.0.0
 * @date 2022-07-24
 * @copyright 版权所有：（鱼香ROS）fishros.org.cn
 */

#include "fish_protocol/fish_protocol.h"

namespace fish_protocol {
std::shared_ptr<FishProtocol>
GetProtocolByConfig(const ProtocolConfig &protocol_config) {
  switch (protocol_config.protocol_type_) {
  case PROTOCOL_TYPE::SERIAL:
    return std::make_shared<SerialProtocol>(protocol_config);
    break;
  case PROTOCOL_TYPE::UDP_SERVER:
    return std::make_shared<UdpServerProtocol>(protocol_config);
    break;
  case PROTOCOL_TYPE::UDP_CLIENT:
    return std::make_shared<UdpClientProtocol>(protocol_config);
    break;
  default:

    break;
  }
  return std::make_shared<SerialProtocol>(protocol_config);
}
}  // namespace fish_protocol
