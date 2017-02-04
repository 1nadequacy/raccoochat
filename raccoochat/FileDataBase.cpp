#include "FileDataBase.h"

#include <boost/algorithm/string.hpp>
#include "SerializationUtils.cpp"
#include "DeserializationUtils.cpp"

#include <algorithm>
#include <fstream>
#include <iostream>

#include <glog/logging.h>

namespace raccoochat {

int32_t FileDataBase::getId(const std::string& dataBasePath) {
  std::ifstream fileIn(dataBasePath, std::ios_base::in);
  CHECK(!!fileIn) << "Cannot open file '" << dataBasePath << "'.";
  std::string userId;
  fileIn >> userId;
  std::ofstream fileOut(dataBasePath, std::ios_base::out);
  CHECK(!!fileOut) << "Cannot open file '" << dataBasePath << "'.";
  fileOut << (stoi(userId) + 1);
  return stoi(userId);
}

void FileDataBase::getUsers(std::map<std::string, int32_t>& cacheUsers,
                            std::map<int32_t, raccoochat::UserData>& cacheUsersData,
                            const std::string& dataBasePath) {
  std::ifstream fileIn(dataBasePath, std::ios_base::in);
  CHECK(!!fileIn) << "Cannot open file '" << dataBasePath << "'.";
  std::string dataInformation;
  while (std::getline (fileIn, dataInformation)) {
    std::vector<std::string> splitData;
    boost::split(splitData, dataInformation, boost::is_any_of("|"));
    if (splitData.empty()) {
      LOG(ERROR) << "Incorrect data: " << dataInformation;
    }
    const int32_t userId = stoi(splitData[0]);
    const std::string& userName = splitData[1];
    cacheUsers[userName] = userId;
    cacheUsersData[userId] = DeserializationUtils::deserialize(splitData);
  }
}

void FileDataBase::getMessages(std::map<int32_t, std::vector<raccoochat::Message>>& cacheArray,
                               const std::string& dataBasePath) {
  std::ifstream fileIn(dataBasePath, std::ios_base::in);
  CHECK(!!fileIn) << "Cannot open file '" << dataBasePath << "'.";
  std::string dataInformation;
  while (std::getline (fileIn, dataInformation)) {
    std::vector<std::string> splitData;
    boost::split(splitData, dataInformation, boost::is_any_of("|"));
    if (splitData.empty()) {
      LOG(ERROR) << "Incorrect data: " << dataInformation;
    }
    const int32_t userId = stoi(splitData[0]);
    cacheArray[userId].push_back(DeserializationUtils::deserialize1(splitData));
  }
}

void FileDataBase::writeUser(const int32_t id,
                             const raccoochat::UserData& user,
                             const std::string& dataBasePath) {
  std::ofstream fileOut(dataBasePath, std::ios_base::app);
  CHECK(!!fileOut) << "Cannot open file '" << dataBasePath << "'.";
  fileOut << SerializationUtils::serialize(id, user) << std::endl;
}

void FileDataBase::writeMessage(const int32_t id,
                                const raccoochat::Message& msg,
                                const std::string& dataBasePath) {
  std::ofstream fileOut(dataBasePath, std::ios_base::app);
  CHECK(!!fileOut) << "Cannot open file '" << dataBasePath << "'.";
  fileOut << SerializationUtils::serialize(id, msg) << std::endl;
}

}
