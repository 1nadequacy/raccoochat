#pragma once

#include "gen-cpp/RaccooChat.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace raccoochat {

class RaccooChatDB {
 public:
  getRegisteredUsers(std::map<std::string, raccoochat::User>&, int32_t, int32_t);
  getUsersData(std::map<int32_t, raccoochat::UserData>&);
};

}
