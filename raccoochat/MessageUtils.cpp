#include "MessageUtils.h"

namespace raccoochat {

raccoochat::Message MessageUtils::createNewMessage(const std::string& sendingTime,
                                                   const int32_t userId,
                                                   const std::string& textMessage) {
  raccoochat::Message newMessage;
  newMessage.sendingTime = sendingTime;
  newMessage.userId = userId;
  newMessage.textMessage = textMessage;
  return newMessage;
}

}
