#include "RaccooChatFileDB.h"
#include "RaccooChatTools.h"
#include "RaccooChatServer.h"
#include "RaccooChatUser.h"

#include <algorithm>
#include <fstream>
#include <regex>

#include <glog/logging.h>

namespace raccoochat {

RaccooChatHandler::RaccooChatHandler() {
  request = new RaccooChatFileDB;
  request->getRegisteredUsers(registeredUsers_, &raccooUsersIndex_, &maxUserNameSize_);
  LOG(INFO) << "All users were got from DataBase";
  request->getUsersData(usersData_, privateMessages_, static_cast<int32_t>(chatMessages_.size()) - 1);
  LOG(INFO) << "All data were got from DataBase";
  request->getAllMessages(chatMessages_);
  LOG(INFO) << "All messages were got from DataBase";
}

RaccooChatHandler::~RaccooChatHandler() {
  request->writeRegisteredUsers(registeredUsers_, raccooUsersIndex_);
  LOG(INFO) << "All users were writen into DataBase";
  request->writeUsersData(usersData_);
  LOG(INFO) << "All data were writen into DataBase";
  request->writeAllMessages(chatMessages_);
  LOG(INFO) << "All messages were writen into DataBase";
}

int32_t RaccooChatHandler::getMaxUserNameSize() {
  return maxUserNameSize_;
}

void RaccooChatHandler::findUser(const std::string& userName) {
  if (!registeredUsers_.count(userName)) {
    InvalidNameException except;
    except.errorCode = 1;
    except.errorMessage = "This user does not exist. Please, try one more time.";
    throw except;
  }
}

void RaccooChatHandler::validateName(const std::string& userName) {
  std::regex reg("^[a-zA-Z][a-zA-Z0-9-_]{3,20}$");
  if (!std::regex_match(userName, reg)) {
    InvalidNameException except;
    except.errorCode = 2;
    except.errorMessage = "Your username is allowed to contain letters, numbers, underscores and has size from 4 to 20 letters.";
    throw except;
  }
  if (registeredUsers_.count(userName)) {
    InvalidNameException except;
    except.errorCode = 3;
    except.errorMessage = "This username is already in use.";
    throw except;
  }
}

void RaccooChatHandler::validatePassword(const std::string& userPassword) {
  std::regex reg("^[a-zA-Z][a-zA-Z0-9]{7,20}$");
  if (!std::regex_match(userPassword, reg)) {
    InvalidNameException except;
    except.errorCode = 4;
    except.errorMessage = "Your password has to contain letters, numbers and has size from 8 to 20 symbols.";
    throw except;
  }
}

void RaccooChatHandler::checkPassword(const std::string& userName,
                                      const std::string& userPassword) {
  if (registeredUsers_[userName].userPassword != RaccooChatTools::codePassword(userPassword)) {
    InvalidNameException except;
    except.errorCode = 5;
    except.errorMessage = "Incorrect password.";
    throw except;
  }
}

void RaccooChatHandler::checkIfUserOnline(const std::string& userName) {
  if (!usersOnline_.count(userName)) {
    InvalidNameException except;
    except.errorCode = 6;
    except.errorMessage = "This user is offline.";
    throw except;
  }
}

void RaccooChatHandler::checkIfUserOffline(const std::string& userName) {
  if (usersOnline_.count(userName)) {
    InvalidNameException except;
    except.errorCode = 7;
    except.errorMessage = "This user is already online.";
    throw except;
  }
}

void RaccooChatHandler::registerUser(const std::string& userName,
                                     const std::string& userPassword) {
  RaccooChatUser newUser;
  registeredUsers_[userName] = newUser.createNewUser(raccooUsersIndex_++, RaccooChatTools::codePassword(userPassword));
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  usersData_[currentUserIndex] = newUser.createNewUserData(privateMessages_, currentUserIndex, userName, static_cast<int32_t>(chatMessages_.size()) - 1);
  maxUserNameSize_ = std::max(maxUserNameSize_, static_cast<int32_t>(userName.size()));
  LOG(INFO) << "User " << userName << "'s registered";
}

void RaccooChatHandler::connectUser(const std::string& userName) {
  usersOnline_[userName] = registeredUsers_[userName];
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  usersData_[currentUserIndex].allMessagesIndex = static_cast<int32_t>(chatMessages_.size()) - 1;
}

void RaccooChatHandler::disconnectUser(const std::string& userName) {
  usersOnline_.erase(userName);
}

void RaccooChatHandler::getAllOnlineUsers(std::vector<std::string>& _return) {
  for (const auto& user: usersOnline_) {
    _return.push_back(user.first);
  }
}

void RaccooChatHandler::getHistory(std::vector<raccoochat::SimpleMessage>& _return) {
  _return = chatMessages_;
}

void RaccooChatHandler::getNewMessages(std::vector<raccoochat::SimpleMessage>& _return,
                                       const std::string& userName) {
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  if (usersData_[currentUserIndex].allMessagesIndex != static_cast<int32_t>(chatMessages_.size()) - 1) {
    _return.assign(chatMessages_.begin() + usersData_[currentUserIndex].allMessagesIndex + 1, chatMessages_.end());
    usersData_[currentUserIndex].allMessagesIndex = static_cast<int32_t>(chatMessages_.size()) - 1;
  }
}

void RaccooChatHandler::getNewPrivateMessages(std::vector<raccoochat::SimpleMessage>& _return,
                                              const std::string& userName) {
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  std::vector<raccoochat::SimpleMessage> userMessages = privateMessages_[currentUserIndex];
  if (usersData_[currentUserIndex].privateMessagesIndex != static_cast<int32_t>(userMessages.size()) - 1) {
    _return.assign(userMessages.begin() + usersData_[currentUserIndex].privateMessagesIndex + 1, userMessages.end());
    usersData_[currentUserIndex].privateMessagesIndex = static_cast<int32_t>(userMessages.size()) - 1;
  }
}

void RaccooChatHandler::addMessage(const raccoochat::SimpleMessage& msg) {
  //RaccooChatTools::removeSpaces(msg);
  chatMessages_.push_back(msg);
  //request->writeAllMessages(chatMessages_);
}

void RaccooChatHandler::addPrivateMessage(const raccoochat::SimpleMessage& msg,
                                          const std::string& userName) {
  const auto& currentUserIndex = registeredUsers_[userName].userIndex;
  //RaccooChatTools::removeSpaces(msg);
  privateMessages_[currentUserIndex].push_back(msg);
}

}
