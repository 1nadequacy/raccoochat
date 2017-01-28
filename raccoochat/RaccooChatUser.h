#pragma once

#include "gen-cpp/RaccooChat.h"

#include <map>
#include <string>
#include <vector>

namespace raccoochat {

class RaccooChatUser {
 public:
  // create a new registered user
  raccoochat::User createNewUser(const int32_t userIndex,
                                 const std::string& userPassword);

  // create a data for new registered user
  raccoochat::UserData createNewUserData(std::map<int32_t, std::vector<raccoochat::SimpleMessage>> privateMessages,
                                         const int32_t userIndex,
                                         const std::string& userName,
                                         const int32_t chatMessagesSize);
};

}
