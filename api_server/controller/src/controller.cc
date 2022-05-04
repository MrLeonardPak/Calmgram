#include "controller.h"

namespace calmgram::api_server::controller {

void Controller::RegisterHandler(std::string type,
                                 std::unique_ptr<IHandler> handler) {
  router_.insert_or_assign(type, std::move(handler));
}

Response Controller::ExecuteHandler(Request const& request) {
  for (auto const& [url, handler] : router_) {
    if (url == request.get_url()) {
      return handler->Execute(request);
    }
  }
}

}  // namespace calmgram::api_server::controller
