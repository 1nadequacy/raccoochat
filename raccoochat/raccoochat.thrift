namespace cpp raccoochat
namespace py raccoochat

const map<string, string> MAP_COMMANDS = {
  '/users': 'returns all users that are online.',
  '/history': 'returns all the messages',
  '/exit': 'sing out from the chat'
  '.{username}': 'send a private message for {username}'
}

struct UserData {
  1: string userName;
  2: string userPassword;
  3: i32 status;
  4: i32 messagesId;
  5: i32 privateMessagesId;
}

struct Message {
  1: string sendingTime;
  2: i32 userId;
  3: string textMessage;
}

exception InvalidNameException {
  1: i32 errorCode;
  2: string errorMessage;
}

service RaccooChat {
  void ifRegisteredUser(1: string userName) throws (1: InvalidNameException e);
  void validateName(1: string userName) throws (1: InvalidNameException e);
  void validatePassword(1: string userPassword) throws (1: InvalidNameException e);
  void comparePassword(1: string userName, 2: string userPassword) throws (1: InvalidNameException e);
  void ifUserOnline(1: string userName) throws (1: InvalidNameException e);
  void ifUserOffline(1: string userName) throws (1: InvalidNameException e);
  void registrationUser(1: string userName, 2: string userPassword);
  i32 connectUser(1: string userName);
  void disconnectUser(1: i32 userId);
  string getUserName(1: i32 userId);
  i32 getUserId(1: string userName);
  set<string> getAllOnlineUsers();
  list<Message> getChatHistory();
  list<Message> getNewMessages(1: i32 userId);
  list<Message> getNewPrivateMessages(1: i32 userId);
  void addMessage(1: Message msg);
  void addPrivateMessage(1: i32 userId, 2: Message msg);
}
