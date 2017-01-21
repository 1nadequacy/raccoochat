#include "RaccooChatServer.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

#include <glog/logging.h>

namespace raccoochat {

raccoochat::User RaccooChatHandler::createNewUser() {
  User newUser;
  newUser.userId = raccooUserId_++;
  newUser.allMessageIndex = chatMessages_.size() - 1;
  std::vector<raccoochat::SimpleMessage> tmpMessages;
  privateMessages_[newUser.userId] = tmpMessages;
  newUser.privateMessageIndex = -1;
  return newUser;
}

std::string RaccooChatHandler::codePassword(const std::string& userPassword) {
  std::string newPassword;
  const char secret = '!';
  for (auto& ch : userPassword) {
    char tmp = ((ch - secret) + (ch - secret)) % 126 + secret;
    newPassword.push_back(tmp);
    newPassword.push_back((ch - secret) % 10 + '0');
  }
  return newPassword;
}

RaccooChatHandler::RaccooChatHandler() {
  std::ifstream fileIn("raccoochat/DataBaseRC/RC_users.txt", std::ios_base::in);
  while (true) {
    std::string userInformation;
    fileIn >> userInformation;
    if (userInformation.size() == 0) break;
    const auto& iterator = userInformation.find('|');
    const std::string userName = userInformation.substr(0, iterator);
    const std::string userPassword = userInformation.substr(iterator + 1, userInformation.size());
    maxUserName_ = std::max(maxUserName_, static_cast<int32_t>(userName.size()));
    usersData_[userName] = createNewUser();
    usersOnline_[userName] = userPassword;
  }
  registeredUsers_ = static_cast<int32_t>(usersOnline_.size());
  fileIn.close();
}

int32_t RaccooChatHandler::getMaxUserName() {
  return maxUserName_;
}

bool RaccooChatHandler::findUser(const std::string& userName) {
  const auto& isUser = usersOnline_.find(userName);
  if (isUser != usersOnline_.end()) {
    return true;
  }
  return false;
}

bool RaccooChatHandler::validateName(const std::string& userName) {
  for (const auto& x : userName) {
    if (x == ' ' || x == '\'' || x == '\"') {
      return false;
    }
  }
  return true;
}

bool RaccooChatHandler::checkPassword(const std::string& userName, const std::string& userPassword) {
  if (usersOnline_[userName] == codePassword(userPassword)) return true;
  else return false;
}

bool RaccooChatHandler::connectUser(const std::string& userName, const std::string& userPassword) {
  usersData_[userName] = createNewUser();
  usersOnline_[userName] = codePassword(userPassword);
  LOG(INFO) << "User " << userName << "'s connected to the chat";
  return true;
}

void RaccooChatHandler::disconnectUser(const std::string& userName) {
  const auto& currentUserId = usersData_[userName].userId;
  usersData_.erase(userName);
  privateMessages_.erase(currentUserId);
  LOG(INFO) << "User " << userName << "'s left from the chat";
}

void RaccooChatHandler::getAllOnlineUsers(std::map<std::string, std::string>& _return) {
  _return = usersOnline_;
}

void RaccooChatHandler::getNewMessages(std::vector<raccoochat::SimpleMessage>& _return, const std::string& userName) {
  std::vector<raccoochat::SimpleMessage> tmpNewMessages;
  if (usersData_[userName].allMessageIndex != static_cast<int32_t>(chatMessages_.size()) - 1) {
    tmpNewMessages.assign(chatMessages_.begin() + usersData_[userName].allMessageIndex + 1, chatMessages_.end());
    usersData_[userName].allMessageIndex = static_cast<int32_t>(chatMessages_.size()) - 1;
  }
  _return = tmpNewMessages;
}

void RaccooChatHandler::getNewPrivateMessages(std::vector<raccoochat::SimpleMessage>& _return, const std::string& userName) {
  std::vector<raccoochat::SimpleMessage> tmpNewPrivateMessages;
  const auto& currectUserId = usersData_[userName].userId;
  std::vector<raccoochat::SimpleMessage> userMessages = privateMessages_[currectUserId];
  if (usersData_[userName].privateMessageIndex != static_cast<int32_t>(userMessages.size()) - 1) {
    tmpNewPrivateMessages.assign(userMessages.begin() + usersData_[userName].privateMessageIndex + 1, userMessages.end());
    usersData_[userName].privateMessageIndex = static_cast<int32_t>(userMessages.size()) - 1;
  }
  _return = tmpNewPrivateMessages;
}

void RaccooChatHandler::getLastFiveMessages(std::vector<raccoochat::SimpleMessage>& _return) {
  std::vector<raccoochat::SimpleMessage> tmpLastFiveMessages;
  if (!chatMessages_.empty()) {
    const int32_t currentSize = chatMessages_.size() - 1;
    const int32_t minIndex = std::min(5, currentSize);
    tmpLastFiveMessages.assign(chatMessages_.end() - minIndex - 1, chatMessages_.end());
  }
  _return = tmpLastFiveMessages;
}

void RaccooChatHandler::addMessage(const raccoochat::SimpleMessage& msg) {
  chatMessages_.push_back(msg);
}

void RaccooChatHandler::addPrivateMessage(const raccoochat::SimpleMessage& msg, const std::string& userName) {
  const int32_t currentUserId = usersData_[userName].userId;
  privateMessages_[currentUserId].push_back(msg);
}

}
