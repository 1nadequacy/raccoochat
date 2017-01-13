#!/usr/local/bin/thrift --gen cpp

namespace cpp tutorial
namespace py tutorial

typedef i32 MyInteger

const map<string, string> MAP_COMMAND = {'users': '/users - returns all users that are online.',
                                         'last': '/last - returns last five messages',
                                         'exit': '/exit - sing out from the chat'}

struct Message {
  1: string time,
  2: string user_name,
  3: string text
}

exception InvalidValueException {
  1: i32 error_code,
  2: string error_msg
}

service RacconChat {
  bool connectUser(1: string user) throws (1: InvalidValueException e),
  void disconnectUser(1: string user) throws (1: InvalidValueException e),
  map<string, i32> getAllOnlineUsers() throws (1: InvalidValueException e),
  list<Message> getNewMessages(1: string user) throws (1: InvalidValueException e),
  list<Message> getLastFiveMessages() throws (1: InvalidValueException e),
  void addMessage(1: Message msg) throws (1: InvalidValueException e)
}
