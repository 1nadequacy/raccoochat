#pragma once

#include "DataBase.h"
#include "gen-cpp/RaccooChat.h"

#include <map>
#include <set>
#include <string>
#include <vector>

namespace raccoochat {

class RaccooChatHandler : virtual public RaccooChatIf {
 public:
  RaccooChatHandler();

  // check if user is registered
  void ifRegisteredUser(const std::string& userName);

  // check if username is valid
  void validateName(const std::string& userName);

  // check if password is valid
  void validatePassword(const std::string& userPassword);

  // check if user has writen correct password
  void comparePassword(const std::string& userName,
                       const std::string& userPassword);

  // check if user is online now
  void ifUserOnline(const std::string& userName);

  // check if user is offline now
  void ifUserOffline(const std::string& userName);

  // register a new user
  void registrationUser(const std::string& userName,
                    const std::string& userPassword);

  // connect user to chat
  int32_t connectUser(const std::string& userName);

  // disconnect user from chat
  void disconnectUser(const int32_t userId);

  // get user name
  void getUserName(std::string& _return, const int32_t userId);

  // get user id
  int32_t getUserId(const std::string& userName);

  // get all the online users
  void getAllOnlineUsers(std::set<std::string>& _return);

  // get all history message
  void getChatHistory(std::vector<raccoochat::Message>& _return);

  // get all the new wrote messages
  void getNewMessages(std::vector<raccoochat::Message>& _return,
                      const int32_t userId);

  // get all the new private messages
  void getNewPrivateMessages(std::vector<raccoochat::Message>& _return,
                             const int32_t userId);

  // add a new message to all the messages
  void addMessage(const raccoochat::Message& msg);

  // add a new private message to all the private messages
  void addPrivateMessage(const int32_t userId,
                         const raccoochat::Message& msg);

 private:
  // pointer to DataBase
  std::unique_ptr<DataBase> request;

  std::set<std::string> usersOnline_;
  std::map<std::string, int32_t> cacheUsers_;
  std::map<int32_t, raccoochat::UserData> cacheUsersData_;
  std::map<int32_t, std::vector<raccoochat::Message>> cacheMessages_;
  std::map<int32_t, std::vector<raccoochat::Message>> cachePrivateMessages_;
};

}
