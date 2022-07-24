#include "fish_protocol/fish_protocol.h"


namespace fish_protocol {
std::shared_ptr<FishProtocol> GetProtocolByConfig(
    const ProtocolConfig& protocol_config) {
  switch (protocol_config.protocol_type_) {
    case PROTOCOL_TYPE::SERIAL:
      return std::make_shared<SerialProtocol>(protocol_config);
      break;
    case PROTOCOL_TYPE::UDP_SERVER:
      return std::make_shared<UdpServerProtocol>(protocol_config);
      break;
    default:
      break;
  }
  return std::make_shared<SerialProtocol>(protocol_config);
}
}  // namespace fish_protocol