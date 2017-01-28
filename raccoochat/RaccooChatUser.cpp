#include "RaccooChatUser.h"

#include <ctime>

namespace raccoochat {

raccoochat::User RaccooChatUser::createNewUser(const int32_t userIndex,
                                               const std::string& userPassword) {
  raccoochat::User newUser;
  newUser.userIndex = userIndex;
  newUser.userPassword = userPassword;
  return newUser;
}

raccoochat::UserData RaccooChatUser::createNewUserData(std::map<int32_t, std::vector<raccoochat::SimpleMessage>> privateMessages,
                                                      const int32_t userIndex,
                                                      const std::string& userName,
                                                      const int32_t chatMessagesSize) {
  raccoochat::UserData newUserData;
  newUserData.userName = userName;
  newUserData.registrationDate = "11.11.2017";        // TODO
  newUserData.allMessagesIndex = chatMessagesSize;
  std::vector<raccoochat::SimpleMessage> tmpMessages;
  privateMessages[userIndex] = tmpMessages;
  newUserData.privateMessagesIndex = -1;
  return newUserData;
}

}
