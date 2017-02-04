#include "FileDataBase.h"
#include "RaccooChatServer.h"
#include "Tools.h"
#include "UserUtils.h"

#include <algorithm>
#include <fstream>
#include <regex>

#include <glog/logging.h>

namespace raccoochat {

RaccooChatHandler::RaccooChatHandler() {
  request = std::unique_ptr<FileDataBase>(new FileDataBase);
  request->getUsers(cacheUsers_,
                    cacheUsersData_,
                    "raccoochat/DataBaseRC/users.txt");
  LOG(INFO) << "All users were got from DataBase";
  request->getMessages(cacheMessages_,
                       "raccoochat/DataBaseRC/messages.txt");
  LOG(INFO) << "All messages were got from DataBase";
  request->getMessages(cachePrivateMessages_,
                       "raccoochat/DataBaseRC/private_messages.txt");
  LOG(INFO) << "All private messages were got from DataBase";
}

void RaccooChatHandler::ifRegisteredUser(const std::string& userName) {
  if (!cacheUsers_.count(userName)) {
    throw Tools::createException(1, "This user does not exist. Please, try one more time.");
  }
}

void RaccooChatHandler::validateName(const std::string& userName) {
  std::regex reg("^[a-zA-Z][a-zA-Z0-9-_]{3,20}$");
  if (!std::regex_match(userName, reg)) {
    throw Tools::createException(2, "Your username is allowed to contain letters, numbers, underscores and has size from 4 to 20 letters.");
  }
  if (cacheUsers_.count(userName)) {
    throw Tools::createException(3, "This username is already in use.");
  }
}

void RaccooChatHandler::validatePassword(const std::string& userPassword) {
  std::regex reg("^[a-zA-Z][a-zA-Z0-9]{7,20}$");
  if (!std::regex_match(userPassword, reg)) {
    throw Tools::createException(4, "Your password has to contain letters, numbers and has size from 8 to 20 symbols.");
  }
}

void RaccooChatHandler::comparePassword(const std::string& userName,
                                        const std::string& userPassword) {
  const int32_t userId = cacheUsers_[userName];
  if (cacheUsersData_[userId].userPassword != Tools::codePassword(userPassword)) {
    throw Tools::createException(5, "Incorrect password.");
  }
}

void RaccooChatHandler::ifUserOnline(const std::string& userName) {
  const int32_t userId = cacheUsers_[userName];
  if (!cacheUsersData_[userId].status) {
    throw Tools::createException(6, "This user is offline.");
  }
}

void RaccooChatHandler::ifUserOffline(const std::string& userName) {
  const int32_t userId = cacheUsers_[userName];
  if (cacheUsersData_[userId].status) {
    throw Tools::createException(7, "This user is already online.");
  }
}

void RaccooChatHandler::registrationUser(const std::string& userName,
                                         const std::string& userPassword) {
  const int32_t userId = request->getId("raccoochat/DataBaseRC/index.txt");
  cacheUsers_[userName] = userId;
  cacheUsersData_[userId] = UserUtils::createNewUserData(userName,
                                                         Tools::codePassword(userPassword),
                                                         static_cast<int32_t>(cacheMessages_[0].size()) - 1,
                                                         -1);
  request->writeUser(userId,
                     cacheUsersData_[userId],
                     "raccoochat/DataBaseRC/users.txt");
  LOG(INFO) << "User " << userName << "'s registered";
}

int32_t RaccooChatHandler::connectUser(const std::string& userName) {
  const int32_t userId = cacheUsers_[userName];
  cacheUsersData_[userId].status = 1;
  cacheUsersData_[userId].messagesId = static_cast<int32_t>(cacheMessages_[0].size()) - 1;
  usersOnline_.insert(userName);
  return userId;
}

void RaccooChatHandler::disconnectUser(const int32_t userId) {
  cacheUsersData_[userId].status = 0;
  const std::string& userName = cacheUsersData_[userId].userName;
  usersOnline_.erase(userName);
}

void RaccooChatHandler::getUserName(std::string& _return, const int32_t userId) {
  _return = cacheUsersData_[userId].userName;
}

int32_t RaccooChatHandler::getUserId(const std::string& userName) {
  return cacheUsers_[userName];
}

void RaccooChatHandler::getAllOnlineUsers(std::set<std::string>& _return) {
  _return = usersOnline_;
}

void RaccooChatHandler::getChatHistory(std::vector<raccoochat::Message>& _return) {
  _return = cacheMessages_[0];
}

void RaccooChatHandler::getNewMessages(std::vector<raccoochat::Message>& _return,
                                       const int32_t userId) {
  if (cacheUsersData_[userId].messagesId != static_cast<int32_t>(cacheMessages_[0].size()) - 1) {
    _return.assign(cacheMessages_[0].begin() + cacheUsersData_[userId].messagesId + 1, cacheMessages_[0].end());
    cacheUsersData_[userId].messagesId = static_cast<int32_t>(cacheMessages_[0].size()) - 1;
  }
}

void RaccooChatHandler::getNewPrivateMessages(std::vector<raccoochat::Message>& _return,
                                              const int32_t userId) {
  if (cacheUsersData_[userId].privateMessagesId != static_cast<int32_t>(cachePrivateMessages_[userId].size()) - 1) {
    _return.assign(cachePrivateMessages_[userId].begin() + cacheUsersData_[userId].privateMessagesId + 1, cachePrivateMessages_[userId].end());
    cacheUsersData_[userId].privateMessagesId = static_cast<int32_t>(cachePrivateMessages_[userId].size()) - 1;
  }
}

void RaccooChatHandler::addMessage(const raccoochat::Message& msg) {
  cacheMessages_[0].push_back(msg);
  request->writeMessage(0, msg, "raccoochat/DataBaseRC/messages.txt");
}

void RaccooChatHandler::addPrivateMessage(const int32_t userId,
                                          const raccoochat::Message& msg) {
  cachePrivateMessages_[userId].push_back(msg);
  request->writeMessage(userId, msg, "raccoochat/DataBaseRC/private_messages.txt");
}

}
