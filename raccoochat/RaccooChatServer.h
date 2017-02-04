#pragma once

#include "gen-cpp/RaccooChat.h"
#include "RaccooChatDB.h"

#include <map>
#include <string>
#include <vector>

namespace raccoochat {

class RaccooChatHandler : virtual public RaccooChatIf {
 public:
  RaccooChatHandler();
  ~RaccooChatHandler();

  // get the longest username
  int32_t getMaxUserNameSize();

  // find username in registered users
  void findUser(const std::string& userName);

  // check if username is valid
  void validateName(const std::string& userName);

  // check if password is valid
  void validatePassword(const std::string& userPassword);

  // check if user has writen correct password
  void checkPassword(const std::string& userName,
                     const std::string& userPassword);

  // check if user is online now
  void checkIfUserOnline(const std::string& userName);

  // check if user is offline now
  void checkIfUserOffline(const std::string& userName);

  // register a new user
  void registerUser(const std::string& userName,
                    const std::string& userPassword);

  // connect user to chat
  void connectUser(const std::string& userName);

  // disconnect user from chat
  void disconnectUser(const std::string& userName);

  // get all the online users
  void getAllOnlineUsers(std::vector<std::string>& _return);

  // get all history message
  void getHistory(std::vector<raccoochat::SimpleMessage>& _return);

  // get all the new wrote messages
  void getNewMessages(std::vector<raccoochat::SimpleMessage>& _return,
                      const std::string& userName);

  // get all the new private messages
  void getNewPrivateMessages(std::vector<raccoochat::SimpleMessage>& _return,
                             const std::string& userName);

  // add a new message to all the messages
  void addMessage(const raccoochat::SimpleMessage& msg);

  // add a new private message to all the private messages
  void addPrivateMessage(const raccoochat::SimpleMessage& msg,
                         const std::string& userName);

 private:
  // pointer to DataBase
  RaccooChatDB *request;

  int32_t raccooUsersIndex_ = 0;
  int32_t maxUserNameSize_ = 0;

  std::map<std::string, raccoochat::User> usersOnline_;
  std::map<std::string, raccoochat::User> registeredUsers_;
  std::map<int32_t, raccoochat::UserData> usersData_;
  std::vector<raccoochat::SimpleMessage> chatMessages_;
  std::map<int32_t, std::vector<raccoochat::SimpleMessage>> privateMessages_;
};

}
