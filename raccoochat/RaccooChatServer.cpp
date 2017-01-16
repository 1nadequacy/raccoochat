#include "RaccooChatServer.h"

#include <vector>
#include <map>
#include <algorithm>

#include <glog/logging.h>

namespace raccoochat {

RaccooChatHandler::RaccooChatHandler() {}

bool RaccooChatHandler::connectUser(const std::string& user) {
  const auto isUser = usersOnline_.find(user);
  if (isUser != usersOnline_.end()) {
    return false;
  }

  LOG(INFO) << "User " << user << "'s connected to the chat";
  usersOnline_[user] = chatMessages_.size() - 1;
  return true;
}

void RaccooChatHandler::disconnectUser(const std::string& user) {
  const auto isUser = usersOnline_.find(user);
  usersOnline_.erase(isUser);
  LOG(INFO) << "User " << user << "'s left from the chat";
}

void RaccooChatHandler::getAllOnlineUsers(std::map<std::string, int32_t>& _return) {
  _return = usersOnline_;
}

void RaccooChatHandler::getNewMessages(std::vector<raccoochat::Message>& _return, const std::string& user) {
  std::vector<raccoochat::Message> tmpNewMessages;
  const auto itUser = usersOnline_.find(user);
  if ((*itUser).second != chatMessages_.size() - 1) {
    tmpNewMessages.assign(chatMessages_.begin() + (*itUser).second + 1, chatMessages_.end());
    (*itUser).second = chatMessages_.size() - 1;
  }
  _return = tmpNewMessages;
}

void RaccooChatHandler::getLastFiveMessages(std::vector<raccoochat::Message>& _return) {
  std::vector<raccoochat::Message> tmpLastFiveMessages;
  if (!chatMessages_.empty()) {
    int32_t currentSize = chatMessages_.size() - 1;
    int32_t minIndex = std::min(5, currentSize);
    tmpLastFiveMessages.assign(chatMessages_.end() - minIndex - 1, chatMessages_.end());
  }
  _return = tmpLastFiveMessages;
}

void RaccooChatHandler::addMessage(const raccoochat::Message& msg) {
  chatMessages_.push_back(msg);
}

}
