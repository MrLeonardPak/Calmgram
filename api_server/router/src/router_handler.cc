#include "router_handler.h"

namespace calmgram::api_server::router {
void RouterHandler::RegisterHandler(IHandler const& handler) {}
Response RouterHandler::ExecuteHandler(Request const& request) {
  Response tmp;
  return tmp;
}
}  // namespace calmgram::api_server::router
