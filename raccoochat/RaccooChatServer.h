#pragma once

#include "gen-cpp/RaccooChat.h"

#include <string>
#include <map>
#include <vector>
#include <iostream>

namespace raccoochat {

class RaccooChatHandler : virtual public RaccooChatIf {
 private:
   raccoochat::User createNewUser();
   std::string codePassword(const std::string&);

 public:
  RaccooChatHandler();
  int32_t getMaxUserName();
  bool findUser(const std::string&);
  bool validateName(const std::string&);
  bool checkPassword(const std::string&, const std::string&);
  bool connectUser(const std::string&, const std::string&);
  void disconnectUser(const std::string&);
  void getAllOnlineUsers(std::map<std::string, std::string>&);
  void getNewMessages(std::vector<raccoochat::SimpleMessage>&, const std::string&);
  void getNewPrivateMessages(std::vector<raccoochat::SimpleMessage>&, const std::string&);
  void getLastFiveMessages(std::vector<raccoochat::SimpleMessage>&);
  void addMessage(const raccoochat::SimpleMessage&);
  void addPrivateMessage(const raccoochat::SimpleMessage&, const std::string&);

 protected:
  int32_t raccooUserId_ = 0;
  int32_t registeredUsers_ = 0;
  int32_t maxUserName_ = 0;
  std::map<std::string, std::string> usersOnline_;
  std::map<std::string, raccoochat::User> usersData_;
  std::vector<raccoochat::SimpleMessage> chatMessages_;
  std::map<int32_t, std::vector<raccoochat::SimpleMessage>> privateMessages_;
};

}

class RaccooChatDB : public raccoochat::RaccooChatHandler {
 public:
   RaccooChatDB();
   void pr_db() { std::cout << "test" << std::endl; };
};
