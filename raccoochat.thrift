namespace cpp raccoochat
namespace py raccoochat

const map<string, string> MAP_COMMAND = {
  'users': '/users - returns all users that are online.',
  'last': '/last - returns last five messages',
  'exit': '/exit - sing out from the chat'
}

struct Message {
  1: string time;
  2: string userName;
  3: string textMessage;
}

exception InvalidValueException {
  1: i32 errorCode;
  2: string errorMessage;
}

service RaccooChat {
  bool connectUser(1: string user);
  void disconnectUser(1: string user);
  map<string, i32> getAllOnlineUsers();
  list<Message> getNewMessages(1: string user);
  list<Message> getLastFiveMessages();
  void addMessage(1: Message msg);
}
