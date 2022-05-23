#include "server_core.h"

// ВНЕШНИЕ ЗАВИСИМОСТИ
#include "async_http_server.h"
#include "json_parser.hpp"
#include "postgre_sql.h"

// CONTROLLER
#include "add_chat_handler.hpp"
#include "send_msg_handler.hpp"
#include "update_chat_handler.hpp"
#include "user_auth_handler.hpp"

// USE CASE
#include "add_chat_uc.h"
#include "send_msg_uc.h"
#include "update_chat_uc.h"
#include "user_auth_uc.h"
// #include "nn.h"
#include "plugs.h"

#include <iostream>
#include <memory>

namespace calmgram::api_server::server {

void ServerCore::Run() {
  try {
    auto db = std::make_shared<libs::database::PostgreSQL const>(
        "user=calmgram host=localhost port=5432 password=calmgram "
        "dbname=calmgram",
        "/home/leonard/technopark/sem_1/Integration_22_05/api_server/libs/"
        "database/"
        "initialScript.sql");
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return;
  }

  auto analyser_text = std::make_shared<TestAnalysisText const>();

  auto add_chat_uc = std::make_unique<use_case::AddChatUC>(db, db, db);
  auto add_chat_handler =
      std::make_unique<controller::AddChatHandler<json::JsonParser>>(
          std::move(add_chat_uc));

  auto send_msg_uc =
      std::make_unique<use_case::SendMsgUC>(db, analyser_text, db);
  auto send_msg_handler =
      std::make_unique<controller::SendMsgHandler<json::JsonParser>>(
          std::move(send_msg_uc));

  auto update_chat_uc = std::make_unique<use_case::UpdateChatUC>(db, db);
  auto update_chat_handler =
      std::make_unique<controller::UpdateChatHandler<json::JsonParser>>(
          std::move(update_chat_uc));

  auto user_auth_uc = std::make_unique<use_case::UserAuthUC>(db, db);
  auto user_auth_handler =
      std::make_unique<controller::UserAuthHandler<json::JsonParser>>(
          std::move(user_auth_uc));

  auto server_controller = std::make_unique<controller::Controller>();

  server_controller->RegisterHandler("/auth", std::move(user_auth_handler));
  //   server_controller->RegisterHandler("/chat/list",
  //                                      std::move(user_auth_handler));
  server_controller->RegisterHandler("/chat/update",
                                     std::move(update_chat_handler));
  server_controller->RegisterHandler("/chat/send", std::move(send_msg_handler));
  server_controller->RegisterHandler("/chat/add", std::move(add_chat_handler));

  try {
    std::make_unique<
        calmgram::api_server::libs::boost::server::AsyncHttpServer>(
        "127.0.0.1", 8888, std::move(server_controller), 2)
        ->Run();
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return;
  }
}

}  // namespace calmgram::api_server::server