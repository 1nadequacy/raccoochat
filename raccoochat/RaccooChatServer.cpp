#include "RaccooChatServer.h"

#include <vector>
#include <map>
#include <algorithm>

#include <glog/logging.h>

namespace raccoochat {

RaccooChatHandler::RaccooChatHandler() {}

raccoochat::User RaccooChatHandler::createNewUser() {
  User newUser;
  newUser.userId = raccooUserIndex++;
  newUser.allMessageIndex = chatMessages_.size() - 1;
  std::vector<raccoochat::SimpleMessage> tmpMessages;
  privateMessages_[newUser.userId] = tmpMessages;
  newUser.privateMessageIndex = -1;
  return newUser;
}

bool RaccooChatHandler::findUser(const std::string& username) {
  const auto isUser = usersOnline_.find(username);
  if (isUser != usersOnline_.end()) {
    return true;
  }
  return false;
}

bool RaccooChatHandler::connectUser(const std::string& username) {
  if (findUser(username)) {
    return false;
  }
  usersOnline_[username] = RaccooChatHandler::createNewUser();
  LOG(INFO) << "User " << username << "'s connected to the chat";
  return true;
}

void RaccooChatHandler::disconnectUser(const std::string& username) {
  int32_t currentUserId = usersOnline_[username].userId;
  usersOnline_.erase(username);
  privateMessages_.erase(currentUserId);
  LOG(INFO) << "User " << username << "'s left from the chat";
}

void RaccooChatHandler::getAllOnlineUsers(std::map<std::string, raccoochat::User>& _return) {
  _return = usersOnline_;
}

void RaccooChatHandler::getNewMessages(std::vector<raccoochat::SimpleMessage>& _return, const std::string& username) {
  std::vector<raccoochat::SimpleMessage> tmpNewMessages;
  if (usersOnline_[username].allMessageIndex != static_cast<int32_t>(chatMessages_.size()) - 1) {
    tmpNewMessages.assign(chatMessages_.begin() + usersOnline_[username].allMessageIndex + 1, chatMessages_.end());
    usersOnline_[username].allMessageIndex = static_cast<int32_t>(chatMessages_.size()) - 1;
  }
  _return = tmpNewMessages;
}

void RaccooChatHandler::getNewPrivateMessages(std::vector<raccoochat::SimpleMessage>& _return, const std::string& username) {
  std::vector<raccoochat::SimpleMessage> tmpNewPrivateMessages;
  int32_t currectUserId = usersOnline_[username].userId;
  std::vector<raccoochat::SimpleMessage> userMessages = privateMessages_[currectUserId];
  if (usersOnline_[username].privateMessageIndex != static_cast<int32_t>(userMessages.size()) - 1) {
    tmpNewPrivateMessages.assign(userMessages.begin() + usersOnline_[username].privateMessageIndex + 1, userMessages.end());
    usersOnline_[username].privateMessageIndex = static_cast<int32_t>(userMessages.size()) - 1;
  }
  _return = tmpNewPrivateMessages;
}

void RaccooChatHandler::getLastFiveMessages(std::vector<raccoochat::SimpleMessage>& _return) {
  std::vector<raccoochat::SimpleMessage> tmpLastFiveMessages;
  if (!chatMessages_.empty()) {
    int32_t currentSize = chatMessages_.size() - 1;
    int32_t minIndex = std::min(5, currentSize);
    tmpLastFiveMessages.assign(chatMessages_.end() - minIndex - 1, chatMessages_.end());
  }
  _return = tmpLastFiveMessages;
}

void RaccooChatHandler::addMessage(const raccoochat::SimpleMessage& msg) {
  chatMessages_.push_back(msg);
}

void RaccooChatHandler::addPrivateMessage(const raccoochat::SimpleMessage& msg, const std::string& username) {
  int32_t currentUserId = usersOnline_[username].userId;
  privateMessages_[currentUserId].push_back(msg);
}

}
