#include "update_chat_handler.h"

namespace calmgram::api_server::router {

bool UpdateChatHandler::ShouldExecute(Request const& request) {
  return true;
}

Response UpdateChatHandler::Execute(Request const& request) {
  Response tmp;
  return tmp;
}

}  // namespace calmgram::api_server::router
