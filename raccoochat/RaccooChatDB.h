#pragma once

#include "gen-cpp/RaccooChat.h"

#include <map>
#include <string>
#include <vector>

namespace raccoochat {

class RaccooChatDB {
 public:
  // get all registered users from DB
  virtual void getRegisteredUsers(std::map<std::string, raccoochat::User>& registeredUsers,
                                  int32_t *raccooUsersIndex,
                                  int32_t *maxUserNameSize) = 0;

  // get users data from DB
  virtual void getUsersData(std::map<int32_t, raccoochat::UserData>& usersData,
                            std::map<int32_t, std::vector<raccoochat::SimpleMessage>> privateMessages,
                            const int32_t chatMessagesSize) = 0;

  // get all the messages from file
  virtual void getAllMessages(std::vector<raccoochat::SimpleMessage>& chatMessages) = 0;

  // write all the registere users into file
  virtual void writeRegisteredUsers(const std::map<std::string, raccoochat::User>& registeredUsers,
                            const int32_t raccooUsersIndex) = 0;

  // write users data into file
  virtual void writeUsersData(const std::map<int32_t, raccoochat::UserData>& usersData) = 0;

  // write all the messages into file
  virtual void writeAllMessages(const std::vector<raccoochat::SimpleMessage>& chatMessages) = 0;
};

}
