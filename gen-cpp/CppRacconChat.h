#include "RacconChat.h"

using namespace ::tutorial;

class RacconChatHandler : virtual public RacconChatIf {
 private:
  std::map<std::string, int32_t> users_online_;
  std::vector<tutorial::Message> messages_;

 public:
  RacconChatHandler();
  bool connectUser(const std::string&);
  void disconnectUser(const std::string&);
  void getAllOnlineUsers(std::map<std::string, int32_t>&);
  void getNewMessages(std::vector<tutorial::Message>&, const std::string&);
  void getLastFiveMessages(std::vector<tutorial::Message>&);
  void addMessage(const tutorial::Message&);
};
