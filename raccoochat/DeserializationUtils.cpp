#include "gen-cpp/RaccooChat.h"
#include "MessageUtils.h"
#include "UserUtils.h"

#include <string>
#include <vector>

namespace raccoochat {

class DeserializationUtils {
 public:
  template <typename T>
  static T deserialize(const std::vector<std::string>& data);
  //static raccoochat::UserData deserialize(const std::vector<std::string>& data);
  //static raccoochat::Message deserialize1(const std::vector<std::string>& data);
};

template <>
raccoochat::UserData DeserializationUtils::deserialize(const std::vector<std::string>& data) {
  raccoochat::UserData newUser = UserUtils::createNewUserData(data[1], data[2], stoi(data[4]), stoi(data[5]));
  return newUser;
}

template <>
raccoochat::Message DeserializationUtils::deserialize(const std::vector<std::string>& data) {
  raccoochat::Message newMessage = MessageUtils::createNewMessage(data[1], stoi(data[2]), data[3]);
  return newMessage;
}

}
