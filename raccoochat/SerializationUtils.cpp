#include "gen-cpp/RaccooChat.h"

#include <string>

namespace raccoochat {

class SerializationUtils {
 public:
  template <typename idT, typename T>
  static std::string serialize(const idT id,
                               const T& data);
};

template <>
std::string SerializationUtils::serialize(const int32_t id,
                                          const raccoochat::UserData& data) {
  std::string user_to_str = std::to_string(id) + '|' + data.userName + '|' + data.userPassword + '|' + '0' + '|' + std::to_string(data.messagesId) + '|' + std::to_string(data.privateMessagesId);
  return user_to_str;
}

template <>
std::string SerializationUtils::serialize(const int32_t id,
                                          const raccoochat::Message& data) {
  std::string msg_to_str = std::to_string(id) + '|' + data.sendingTime + '|' + std::to_string(data.userId) + '|' + data.textMessage;
  return msg_to_str;
}


}
