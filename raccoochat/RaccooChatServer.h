#pragma once

#include "gen-cpp/RaccooChat.h"

#include <map>
#include <string>
#include <vector>

namespace raccoochat {

class RaccooChatHandler : virtual public RaccooChatIf {
 private:
  std::string codePassword(const std::string&);
  raccoochat::User createNewUser(const std::string&);
  raccoochat::UserData createNewUserData(const int32_t, const std::string&);

  int32_t raccooUsersIndex_ = 0;
  int32_t maxUserNameSize_ = 0;
  std::map<std::string, raccoochat::User> registeredUsers_;
  std::map<int32_t, raccoochat::UserData> usersData_;
  std::vector<raccoochat::SimpleMessage> chatMessages_;
  std::map<int32_t, std::vector<raccoochat::SimpleMessage>> privateMessages_;

 public:
  RaccooChatHandler();
  int32_t getMaxUserNameSize();
  bool findUser(const std::string&);
  bool validateName(const std::string&);
  bool checkPassword(const std::string&, const std::string&);
  bool connectUser(const std::string&, const std::string&);
  void disconnectUser(const std::string&);
  void getAllOnlineUsers(std::vector<std::string>&);
  void getNewMessages(std::vector<raccoochat::SimpleMessage>&, const std::string&);
  void getNewPrivateMessages(std::vector<raccoochat::SimpleMessage>&, const std::string&);
  void addMessage(const raccoochat::SimpleMessage&);
  void addPrivateMessage(const raccoochat::SimpleMessage&, const std::string&);
};

}
