#pragma once

#include "gen-cpp/RaccooChat.h"

#include <map>
#include <string>
#include <vector>

namespace raccoochat {

struct UserUtils {
  // create a data for new registered user
  static raccoochat::UserData createNewUserData(const std::string& userName,
                                                const std::string& userPassword,
                                                const int32_t chatMessagesId,
                                                const int32_t chatPrivateMessagesId);
};

}
