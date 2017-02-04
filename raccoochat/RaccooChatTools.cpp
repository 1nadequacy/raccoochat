#include "RaccooChatTools.h"

#include <regex>

namespace {
  const char kSecretChar = '!';
}

namespace raccoochat {

std::string RaccooChatTools::codePassword(const std::string& userPassword) {
  std::string newPassword;
  for (auto& ch : userPassword) {
    char tmp = ((ch - kSecretChar) + (ch - kSecretChar)) % 126 + kSecretChar;
    newPassword.push_back(tmp);
    newPassword.push_back((ch - kSecretChar) % 10 + '0');
  }
  return newPassword;
}

void RaccooChatTools::removeSpaces(raccoochat::SimpleMessage& msg) {
  std::regex reg(" {2,}");
  std::regex_replace(msg.textMessage, reg, " ");
}

}
