#include "UserUtils.h"

namespace raccoochat {

raccoochat::UserData UserUtils::createNewUserData(const std::string& userName,
                                                  const std::string& userPassword,
                                                  const int32_t chatMessagesId,
                                                  const int32_t chatPrivateMessagesId) {
  raccoochat::UserData newUserData;
  newUserData.userName = userName;
  newUserData.userPassword = userPassword;
  newUserData.status = 0;
  newUserData.messagesId = chatMessagesId;
  newUserData.privateMessagesId = chatPrivateMessagesId;
  return newUserData;
}

}
