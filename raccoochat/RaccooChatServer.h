#pragma once

#include "gen-cpp/RaccooChat.h"

#include <string>
#include <map>
#include <vector>

namespace raccoochat {

class RaccooChatHandler : virtual public RaccooChatIf {
 public:
  RaccooChatHandler();
  raccoochat::User createNewUser();
  bool findUser(const std::string&);
  bool connectUser(const std::string&);
  void disconnectUser(const std::string&);
  void getAllOnlineUsers(std::map<std::string, raccoochat::User>&);
  void getNewMessages(std::vector<raccoochat::SimpleMessage>&, const std::string&);
  void getNewPrivateMessages(std::vector<raccoochat::SimpleMessage>&, const std::string&);
  void getLastFiveMessages(std::vector<raccoochat::SimpleMessage>&);
  void addMessage(const raccoochat::SimpleMessage&);
  void addPrivateMessage(const raccoochat::SimpleMessage&, const std::string&);

 private:
  int32_t raccooUserIndex = 0;
  std::map<std::string, raccoochat::User> usersOnline_;
  std::vector<raccoochat::SimpleMessage> chatMessages_;
  std::map<int32_t, std::vector<raccoochat::SimpleMessage>> privateMessages_;
};

}
