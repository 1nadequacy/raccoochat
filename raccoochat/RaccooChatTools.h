#pragma once

#include "gen-cpp/RaccooChat.h"

#include <string>

namespace raccoochat {

class RaccooChatTools {
 public:
  // code the password
  static std::string codePassword(const std::string& userPassword);

  // remove all the extra spaces in message
  static void removeSpaces(raccoochat::SimpleMessage& msg);
};

}
