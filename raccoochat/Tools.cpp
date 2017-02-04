#include "MessageUtils.h"
#include "Tools.h"

#include <regex>

namespace {
  const char kSecretChar = '!';
}

namespace raccoochat {

std::string Tools::codePassword(const std::string& userPassword) {
  std::string newPassword;
  for (auto& ch : userPassword) {
    const char tmp = ((ch - kSecretChar) + (ch - kSecretChar)) % 126 + kSecretChar;
    newPassword.push_back(tmp);
    newPassword.push_back((ch - kSecretChar) % 10 + '0');
  }
  return newPassword;
}

InvalidNameException Tools::createException(const int32_t errorCode,
                                            const std::string& errorMessage) {
  InvalidNameException except;
  except.errorCode = errorCode;
  except.errorMessage = errorMessage;
  return except;
}

}
