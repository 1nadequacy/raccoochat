#include "RaccooChatDB.cpp"
#include "RaccooChatDB.h"
#include "RaccooChatServer.h"

#include <algorithm>
#include <ctime>
#include <fstream>

#include <glog/logging.h>

namespace raccoochat {

std::string RaccooChatHandler::codePassword(const std::string& userPassword) {
  std::string newPassword;
  const char& secret = '!';
  for (auto& ch : userPassword) {
    char tmp = ((ch - secret) + (ch - secret)) % 126 + secret;
    newPassword.push_back(tmp);
    newPassword.push_back((ch - secret) % 10 + '0');
  }
  return newPassword;
}

raccoochat::User RaccooChatHandler::createNewUser(const std::string& userPassword) {
  User newUser;
  newUser.userIndex = raccooUsersIndex_++;
  newUser.userPassword = codePassword(userPassword);
  return newUser;
}

raccoochat::UserData RaccooChatHandler::createNewUserData(const int32_t userIndex, const std::string& userName) {
  UserData newUserData;
  newUserData.userName = userName;
  newUserData.registrationDate = "11.11.2017";
  newUserData.status = 1;
  newUserData.allMessagesIndex = static_cast<int32_t>(chatMessages_.size()) - 1;
  std::vector<raccoochat::SimpleMessage> tmpMessages;
  privateMessages_[userIndex] = tmpMessages;
  newUserData.privateMessagesIndex = -1;
  return newUserData;
}

RaccooChatHandler::RaccooChatHandler() {
  RaccooChatDB::RaccooChatDB request;
  request.getRegisteredUsers(registeredUsers_, raccooUsersIndex_, maxUserNameSize_);
  LOG(INFO) << "All users were got from DataBase";
  request.getUsersData(usersData_);
  LOG(INFO) << "All data were got from DataBase";
  std::cout << maxUserNameSize_ << std::endl;
}

int32_t RaccooChatHandler::getMaxUserNameSize() {
  return maxUserNameSize_;
}

bool RaccooChatHandler::findUser(const std::string& userName) {
  const auto& isUser = registeredUsers_.find(userName);
  if (isUser != registeredUsers_.end()) {
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
  if (registeredUsers_[userName].userPassword == codePassword(userPassword)) return true;
  else return false;
}

bool RaccooChatHandler::connectUser(const std::string& userName, const std::string& userPassword) {
  registeredUsers_[userName] = createNewUser(userPassword);
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  usersData_[currentUserIndex] = createNewUserData(currentUserIndex, userName);
  LOG(INFO) << "User " << userName << "'s connected to the chat";
  return true;
}

void RaccooChatHandler::disconnectUser(const std::string& userName) {
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  usersData_[currentUserIndex].status = 0;
  LOG(INFO) << "User " << userName << "'s left from the chat";
}

void RaccooChatHandler::getAllOnlineUsers(std::vector<std::string>& _return) {
  std::vector<std::string> usersOnline;
  for (auto& user : usersData_) {
    if (user.second.status == 1) {
      usersOnline.push_back(user.second.userName);
    }
  }
  _return = usersOnline;
}

void RaccooChatHandler::getNewMessages(std::vector<raccoochat::SimpleMessage>& _return, const std::string& userName) {
  std::vector<raccoochat::SimpleMessage> tmpNewMessages;
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  if (usersData_[currentUserIndex].allMessagesIndex != static_cast<int32_t>(chatMessages_.size()) - 1) {
    tmpNewMessages.assign(chatMessages_.begin() + usersData_[currentUserIndex].allMessagesIndex + 1, chatMessages_.end());
    usersData_[currentUserIndex].allMessagesIndex = static_cast<int32_t>(chatMessages_.size()) - 1;
  }
  _return = tmpNewMessages;
}

void RaccooChatHandler::getNewPrivateMessages(std::vector<raccoochat::SimpleMessage>& _return, const std::string& userName) {
  std::vector<raccoochat::SimpleMessage> tmpNewPrivateMessages;
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  std::vector<raccoochat::SimpleMessage> userMessages = privateMessages_[currentUserIndex];
  if (usersData_[currentUserIndex].privateMessagesIndex != static_cast<int32_t>(userMessages.size()) - 1) {
    tmpNewPrivateMessages.assign(userMessages.begin() + usersData_[currentUserIndex].privateMessagesIndex + 1, userMessages.end());
    usersData_[currentUserIndex].privateMessagesIndex = static_cast<int32_t>(userMessages.size()) - 1;
  }
  _return = tmpNewPrivateMessages;
}

void RaccooChatHandler::addMessage(const raccoochat::SimpleMessage& msg) {
  chatMessages_.push_back(msg);
}

void RaccooChatHandler::addPrivateMessage(const raccoochat::SimpleMessage& msg, const std::string& userName) {
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  privateMessages_[currentUserIndex].push_back(msg);
}

}
