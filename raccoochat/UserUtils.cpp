#include "UserUtils.h"

namespace raccoochat {

raccoochat::UserData UserUtils::createNewUserData(const std::string& userName,
                                                  const std::string& userPassword,
                                                  const int32_t chatMessagesSize) {
  raccoochat::UserData newUserData;
  newUserData.userName = userName;
  newUserData.userPassword = userPassword;
  newUserData.status = 0;
  newUserData.messagesId = chatMessagesSize;
  newUserData.privateMessagesId = -1;
  return newUserData;
}

}
