#include "controller.h"

namespace calmgram::api_server::controller {

void Controller::RegisterHandler(std::string type,
                                 std::unique_ptr<IHandler> handler) {
  router_.insert_or_assign(type, std::move(handler));
}

Response Controller::ExecuteHandler(Request const& request) {
  std::string path = request.get_path();
  try {
    return router_.at(path)->Handle(request);
  } catch (std::out_of_range) {
    // TODO: 404 нет страницы
    Response bad_response(Response::NOT_PAGE, {});
    return bad_response;
  }
}

}  // namespace calmgram::api_server::controller
