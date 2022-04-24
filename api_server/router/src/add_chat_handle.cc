#include "add_chat_handler.h"

namespace calmgram::api_server::router {

bool AddChatHandler::ShouldExecute(Request const& request) {
  return true;
}

Response AddChatHandler::Execute(Request const& request) {
  Response tmp;
  return tmp;
}

}  // namespace calmgram::api_server::router
