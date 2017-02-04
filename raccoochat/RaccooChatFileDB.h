#pragma once

#include "gen-cpp/RaccooChat.h"
#include "RaccooChatDB.h"

#include <map>
#include <string>
#include <vector>

namespace raccoochat {

class RaccooChatFileDB : virtual public RaccooChatDB {
 public:
  // get all the registered users from file
  void getRegisteredUsers(std::map<std::string, raccoochat::User>& registeredUsers,
                                  int32_t *raccooUsersIndex,
                                  int32_t *maxUserNameSize);

  // get users data from file
  void getUsersData(std::map<int32_t, raccoochat::UserData>& usersData,
                            std::map<int32_t, std::vector<raccoochat::SimpleMessage>> privateMessages,
                            const int32_t chatMessagesSize);

  // get all the messages from file
  void getAllMessages(std::vector<raccoochat::SimpleMessage>& chatMessages);

  // write all the registere users into file
  void writeRegisteredUsers(const std::map<std::string, raccoochat::User>& registeredUsers,
                            const int32_t raccooUsersIndex);

  // write users data into file
  void writeUsersData(const std::map<int32_t, raccoochat::UserData>& usersData);

  // write all the messages into file
  void writeAllMessages(const std::vector<raccoochat::SimpleMessage>& chatMessages);
};

}
