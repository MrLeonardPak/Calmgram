#include "controller.h"

namespace calmgram::api_server::controller {

void Controller::RegisterHandler(std::string const& url,
                                 std::unique_ptr<IHandler>&& handler) {
  router_.insert_or_assign(url, std::move(handler));
}

Response Controller::ExecuteHandler(Request const& request) {
  std::string path = request.get_path();
  try {
    return router_.at(path)->Handle(request);
  } catch (std::exception const& e) {
    std::cout << e.what() << '\n';
    return {Response::NOT_PAGE, {}};
  }
}

}  // namespace calmgram::api_server::controller
