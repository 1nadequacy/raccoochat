#pragma once

#include "RaccooChat.h"

using namespace ::raccoochat;

class RaccooChatHandler : virtual public RaccooChatIf {
 public:
  RaccooChatHandler();
  bool connectUser(const std::string&);
  void disconnectUser(const std::string&);
  void getAllOnlineUsers(std::map<std::string, int32_t>&);
  void getNewMessages(std::vector<raccoochat::Message>&, const std::string&);
  void getLastFiveMessages(std::vector<raccoochat::Message>&);
  void addMessage(const raccoochat::Message&);

 private:
  std::map<std::string, int32_t> usersOnline_;
  std::vector<raccoochat::Message> chatMessages_;
};
