#pragma once

#include "gen-cpp/RaccooChat.h"

#include <string>

namespace raccoochat {

struct Tools {
  // code the password
  static std::string codePassword(const std::string& userPassword);

  // construct an exception
  static InvalidNameException createException(const int32_t errorCode,
                                              const std::string& errorMessage);
};

}
