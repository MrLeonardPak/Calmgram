#include "server_core.h"
#include "async_http_server.h"
#include "controller.h"

#include <iostream>

namespace calmgram::api_server::server {

// HACK: Тестовый обработчки
class AdminHandler : public controller::IHandler {
 public:
  controller::Response Handle(controller::IRequest const& request) {
    std::cout << "FROM: " << request.get_path() << std::endl;
    std::cout << "BODY: " << request.get_body() << std::endl;
    return {controller::Response::OK, "Oh My God!"};
  }
};

void ServerCore::Run() {
  auto server_controller = std::make_unique<controller::Controller>();
  auto admin_handler = std::make_unique<AdminHandler>();
  // TODO: Заполнить роутер обработчиками
  server_controller->RegisterHandler("/admin", std::move(admin_handler));
  try {
    std::make_unique<
        calmgram::api_server::libs::boost::server::AsyncHttpServer>(
        "127.0.0.1", 8888, std::move(server_controller), 2)
        ->Run();
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
  }
}

}  // namespace calmgram::api_server::server