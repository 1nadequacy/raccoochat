#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "RacconChat.h"
#include "CppRacconChat.h"

using namespace ::std;
using namespace ::tutorial;

RacconChatHandler::RacconChatHandler() {}

bool RacconChatHandler::connectUser(const string& user) {
  auto isUser = users_online_.find(user);
  if (isUser != users_online_.end()) return false;
  cout << "User " << user << "'s connected to chat." << endl;
  users_online_[user] = messages_.size() - 1;
  return true;
}

void RacconChatHandler::disconnectUser(const string& user) {
  auto isUser = users_online_.find(user);
  users_online_.erase(isUser);
  cout << "User " << user << "'s left from the chat." << endl;
}

void RacconChatHandler::getAllOnlineUsers(map<string, int32_t>& _return) {
  _return = users_online_;
}

void RacconChatHandler::getNewMessages(vector<tutorial::Message>& _return, const string& user) {
  vector<tutorial::Message> tmp_new_messages;
  auto itUser = users_online_.find(user);
  if ((*itUser).second != messages_.size() - 1) {
    tmp_new_messages.assign(messages_.begin() + (*itUser).second + 1, messages_.end());
    (*itUser).second = messages_.size() - 1;
  }
  _return = tmp_new_messages;
}

void RacconChatHandler::getLastFiveMessages(vector<tutorial::Message>& _return) {
  vector<tutorial::Message> tmp_last_five_messages;
  if (!messages_.empty()) {
    int32_t current_size = messages_.size() - 1;
    int32_t min_index = min(5, current_size);
    tmp_last_five_messages.assign(messages_.end() - min_index - 1, messages_.end());
  }
  _return = tmp_last_five_messages;
}

void RacconChatHandler::addMessage(const tutorial::Message& msg) {
  messages_.push_back(msg);
}
