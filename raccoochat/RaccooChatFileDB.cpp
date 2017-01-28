#include "RaccooChatFileDB.h"
#include "RaccooChatUser.h"

#include <boost/algorithm/string.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

namespace raccoochat {

void RaccooChatFileDB::getRegisteredUsers(std::map<std::string, raccoochat::User>& registeredUsers,
                                      int32_t *raccooUsersIndex,
                                      int32_t *maxUserNameSize) {
  std::ifstream fileIn("raccoochat/DataBaseRC/RC_users.txt", std::ios_base::in);
  std::string usersIndex;
  fileIn >> usersIndex;
  *raccooUsersIndex = stoi(usersIndex);
  while (true) {
    std::string userInformation;
    fileIn >> userInformation;
    if (static_cast<int32_t>(userInformation.size()) == 0) break;
    std::vector<std::string> registeredUser;
    boost::split(registeredUser, userInformation, boost::is_any_of("|"));
    const std::string& userName = registeredUser[0];
    raccoochat::RaccooChatUser newUser;
    registeredUsers[userName] = newUser.createNewUser(stoi(registeredUser[1]), registeredUser[2]);
    *maxUserNameSize = std::max(*maxUserNameSize, static_cast<int32_t>(userName.size()));
  }
  fileIn.close();
}

void RaccooChatFileDB::getUsersData(std::map<int32_t, raccoochat::UserData>& usersData,
                                std::map<int32_t, std::vector<raccoochat::SimpleMessage>> privateMessages,
                                const int32_t chatMessagesSize) {
  std::ifstream fileIn("raccoochat/DataBaseRC/RC_users_data.txt", std::ios_base::in);
  while (true) {
    std::string userInformation;
    fileIn >> userInformation;
    if (static_cast<int32_t>(userInformation.size()) == 0) break;
    std::vector<std::string> userData;
    boost::split(userData, userInformation, boost::is_any_of("|"));
    const int32_t userIndex = stoi(userData[0]);
    const std::string& userName = userData[1];
    raccoochat::RaccooChatUser newUserData;
    usersData[userIndex] = newUserData.createNewUserData(privateMessages, userIndex, userName, chatMessagesSize);
  }
  fileIn.close();
}

void RaccooChatFileDB::getAllMessages(std::vector<raccoochat::SimpleMessage>& chatMessages) {
  std::ifstream fileIn("raccoochat/DataBaseRC/RC_chat.txt", std::ios_base::in);
  while (true) {
    std::string messageData;
    std::getline (fileIn, messageData);
    if (static_cast<int32_t>(messageData.size()) == 0) break;
    std::vector<std::string> simpleMessage;
    boost::split(simpleMessage, messageData, boost::is_any_of("|"));
    raccoochat::SimpleMessage message;
    message.time = simpleMessage[0];
    message.userName = simpleMessage[1];
    message.textMessage = simpleMessage[2];
    chatMessages.push_back(message);
  }
  fileIn.close();
}

void RaccooChatFileDB::writeRegisteredUsers(const std::map<std::string, raccoochat::User>& registeredUsers,
                                      const int32_t raccooUsersIndex) {
  std::ofstream fileOut("raccoochat/DataBaseRC/RC_users.txt", std::ios_base::out);
  fileOut << raccooUsersIndex << std::endl;
  for (const auto& user: registeredUsers) {
    fileOut << user.first << '|' << user.second.userIndex << '|' << user.second.userPassword << std::endl;
  }
  fileOut.close();
}

void RaccooChatFileDB::writeUsersData(const std::map<int32_t, raccoochat::UserData>& usersData) {
  std::ofstream fileOut("raccoochat/DataBaseRC/RC_users_data.txt", std::ios_base::out);
  for (const auto& user: usersData) {
    fileOut << user.first << '|' << user.second.userName << '|' << user.second.registrationDate << '|' << user.second.allMessagesIndex << '|' << user.second.privateMessagesIndex << std::endl;
  }
  fileOut.close();
}

void RaccooChatFileDB::writeAllMessages(const std::vector<raccoochat::SimpleMessage>& chatMessages) {
  std::ofstream fileOut("raccoochat/DataBaseRC/RC_chat.txt", std::ios_base::out);
  for (const auto& message: chatMessages) {
    fileOut << message.time << '|' << message.userName << '|' << message.textMessage << std::endl;
  }
  fileOut.close();
}

}
