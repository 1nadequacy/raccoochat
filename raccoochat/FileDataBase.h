#pragma once

#include "gen-cpp/RaccooChat.h"
#include "DataBase.h"

#include <map>
#include <string>
#include <vector>

namespace raccoochat {

class FileDataBase : public DataBase {
 public:
  // get the next available id for a new user
  virtual int32_t getId(const std::string& dataBasePath) override;

  // get users from the data base
  virtual void getUsers(std::map<std::string, int32_t>& cacheUsers,
                        std::map<int32_t, raccoochat::UserData>& cacheUsersData,
                        const std::string& dataBasePath) override;

  // get messages from the data base
  virtual void getMessages(std::map<int32_t, std::vector<raccoochat::Message>>& cacheArray,
                           const std::string& dataBasePath) override;

  // write users to the data base
  virtual void writeUser(const int32_t id,
                         const raccoochat::UserData& user,
                         const std::string& dataBasePath) override;

  // write messages to the data base
  virtual void writeMessage(const int32_t id,
                            const raccoochat::Message& msg,
                            const std::string& dataBasePath) override;
};

}
