#include "server_core.h"
#include "async_http_server.h"
#include "controller.h"
#include "interfaces_uc_input.h"
#include "json_parser.hpp"
#include "user_auth_handler.hpp"
#include "user_auth_uc.h"

#include <iostream>

namespace calmgram::api_server::server {

// HACK: Тестовый Handler
class AdminHandler : public controller::IHandler {
 public:
  controller::Response Handle(controller::IRequest const& request) {
    std::cout << "FROM: " << request.get_path() << std::endl;
    std::cout << "BODY: " << request.get_body() << std::endl;
    return {controller::Response::OK, "Oh My God!"};
  }
};
// HACK: Тестовый UserAuthUC
class TestUserAuthUC : public use_case::IUserAuthUC {
 public:
  std::vector<int> Execute(int user_id) { return {1, 2, 3, 0, 0, user_id}; }
};

void ServerCore::Run() {
  auto user_auth_uc = std::make_unique<TestUserAuthUC>();
  auto user_auth_handler =
      std::make_unique<controller::UserAuthHandler<json::JsonParser>>(
          std::move(user_auth_uc));
  // TODO: Заполнить роутер обработчиками
  auto server_controller = std::make_unique<controller::Controller>();
  auto admin_handler = std::make_unique<AdminHandler>();
  server_controller->RegisterHandler("/admin", std::move(admin_handler));
  server_controller->RegisterHandler("/auth", std::move(user_auth_handler));
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