#include "controller.h"

#include <iostream>

namespace calmgram::api_server::controller {

void Controller::RegisterHandler(std::string const& url,
                                 std::unique_ptr<IHandler>&& handler) {
  router_.insert_or_assign(url, std::move(handler));
}

Response Controller::ExecuteHandler(IRequest const& request) {
  std::string path = request.get_path();
  try {
    return router_.at(path)->Handle(request);
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << " " << path
              << '\n';
    return {Response::NOT_PAGE, {}};
  }
}

}  // namespace calmgram::api_server::controller
