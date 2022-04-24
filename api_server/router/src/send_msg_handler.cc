#include "send_msg_handler.h"

namespace calmgram::api_server::router {

bool SendMsgHandler::ShouldExecute(Request const& request) {
  return true;
}

Response SendMsgHandler::Execute(Request const& request) {
  Response tmp;
  return tmp;
}

}  // namespace calmgram::api_server::router
