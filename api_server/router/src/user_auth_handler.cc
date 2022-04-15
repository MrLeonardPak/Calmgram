#include "user_auth_handler.h"

namespace calmgram::api_server::router {

bool UserAuthHandler::ShouldExecute(Request const& request) {
  return true;
}

Response UserAuthHandler::Execute(Request const& request) {
  Response tmp;
  return tmp;
}

}  // namespace calmgram::api_server::router
