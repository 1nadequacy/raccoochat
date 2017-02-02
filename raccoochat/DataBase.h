#pragma once

#include "gen-cpp/RaccooChat.h"

#include <map>
#include <string>
#include <vector>

namespace raccoochat {

class DataBase {
 public:
  // get current index for new user
  virtual int32_t getId(const std::string& dataBasePath) = 0;

  // get users from data base
  virtual void getUsers(std::map<std::string, int32_t>& cacheUsers,
                        std::map<int32_t, raccoochat::UserData>& cacheUsersData,
                        const std::string& dataBasePath) = 0;

  // get data from data base
  virtual void getMessages(std::map<int32_t, std::vector<raccoochat::Message>>& cacheArray,
                           const std::string& dataBasePath) = 0;

  // write users to data base
  virtual void writeUser(const int32_t id,
                         const raccoochat::UserData& user,
                         const std::string& dataBasePath) = 0;

  // write data to data base
  virtual void writeMessage(const int32_t id,
                         const raccoochat::Message& msg,
                         const std::string& dataBasePath) = 0;
};

}
