#pragma once

#include "gen-cpp/RaccooChat.h"

#include <map>
#include <string>
#include <vector>

namespace raccoochat {

struct MessageUtils {
  // create a new message
  static raccoochat::Message createNewMessage(const std::string& sendingTime,
                                       const int32_t userId,
                                       const std::string& textMessage);
};

}
