#include "RaccooChatDB.h"
#include "RaccooChatServer.h"

#include <algorithm>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>

namespace raccoochat {

void RaccooChatDB::getRegisteredUsers(std::map<std::string, raccoochat::User>& registeredUsers, int32_t raccooUsersIndex, int32_t maxUserNameSize) {
  std::ifstream fileIn("raccoochat/DataBaseRC/RC_users.txt", std::ios_base::in);
  fileIn >> raccooUsersIndex;
  while (true) {
    std::string userInformation;
    fileIn >> userInformation;
    if (static_cast<int32_t>(userInformation.size()) == 0) break;
    std::vector<std::string> registeredUser;
    boost::split(registeredUser, userInformation, boost::is_any_of("|"));
    const std::string userName = registeredUser[0];
    registeredUsers[userName] = RaccooChatHandler::createNewUser(userName);
    registeredUsers[userName].userIndex = static_cast<int>(registeredUser[1]);
    registeredUsers[userName].userPassword = registeredUser[2];
    maxUserNameSize = std::max(maxUserNameSize, static_cast<int32_t>(userName.size()));
  }
  fileIn.close();
}

void RaccooChatDB::getUsersData(std::map<int32_t, raccoochat::UserData>& usersData) {
  std::ifstream fileIn("raccoochat/DataBaseRC/RC_users_data.txt", std::ios_base::in);
  while (true) {
    std::string userInformation;
    fileIn >> userInformation;
    if (static_cast<int32_t>(userInformation.size()) == 0) break;
    std::vector<std::string> userData;
    boost::split(userData, userInformation, boost::is_any_of("|"));
    const auto& userIndex = static_cast<int32_t>(userData[0]);
    const std::string& userName = userData[1];
    usersData[userIndex] = RaccooChatHandler::createNewUserData(userIndex, userName);
    usersData[userIndex].registrationDate = userData[2];
    usersData[userIndex].status = static_cast<bool>(userData[3]);
    usersData[userIndex].allMessagesIndex = static_cast<int32_t>(userData[4]);
    usersData[userIndex].privateMessagesIndex = static_cast<int32_t>(userData[5]);
  }
  fileIn.close();
}

}
