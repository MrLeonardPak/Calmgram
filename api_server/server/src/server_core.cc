#include "server_core.h"

// ВНЕШНИЕ ЗАВИСИМОСТИ
#include "async_http_server.h"
#include "json_parser.hpp"
#include "postgre_sql.h"

// SESSION
#include "session_controller.h"

// CONTROLLER
#include "add_chat_handler.hpp"
#include "add_to_dataset_handler.hpp"
#include "get_chat_list_handler.hpp"
#include "send_msg_handler.hpp"
#include "update_chat_handler.hpp"
#include "user_auth_handler.hpp"
#include "user_logout_handler.hpp"

// USE CASE
#include "add_chat_uc.h"
#include "add_to_dataset_uc.h"
#include "get_chat_list_uc.h"
#include "send_msg_uc.h"
#include "update_chat_uc.h"
#include "user_auth_uc.h"
#include "user_logout_uc.h"

#include "plugs.h"
// #include "dataset.h"
// #include "nn.h"

#include <iostream>
#include <memory>

namespace calmgram::api_server::server {

void ServerCore::Run() {
  try {
    auto connection = std::getenv(kConnectionDB);
    auto initional = std::getenv(kInitionalDB);
    auto host = std::getenv(kHost);
    auto port = std::getenv(kPort);

    if (connection == nullptr || initional == nullptr || host == nullptr ||
        port == nullptr) {
      throw std::runtime_error("No environment variable!");
    }

    auto db = std::make_shared<libs::database::PostgreSQL const>(connection,
                                                                 initional);

    auto session_control = std::make_shared<session::SessionController>();

    auto analyser_text = std::make_shared<TestAnalysisText const>();
    auto adder_dataset = std::make_shared<TestAdditionalDataset const>();

    // auto analyser_text = std::make_shared<ml::nn::NN const>();
    // auto adder_dataset = std::make_shared<ml::data::Dataset const>();

    auto user_auth_uc =
        std::make_unique<use_case::UserAuthUC>(db, db, session_control);
    auto user_auth_handler =
        std::make_unique<controller::UserAuthHandler<json::JsonParser>>(
            std::move(user_auth_uc));

    auto update_chat_uc =
        std::make_unique<use_case::UpdateChatUC>(session_control, db, db);
    auto update_chat_handler =
        std::make_unique<controller::UpdateChatHandler<json::JsonParser>>(
            std::move(update_chat_uc));

    auto send_msg_uc = std::make_unique<use_case::SendMsgUC>(
        session_control, db, analyser_text, db);
    auto send_msg_handler =
        std::make_unique<controller::SendMsgHandler<json::JsonParser>>(
            std::move(send_msg_uc));

    auto add_chat_uc =
        std::make_unique<use_case::AddChatUC>(session_control, db, db);
    auto add_chat_handler =
        std::make_unique<controller::AddChatHandler<json::JsonParser>>(
            std::move(add_chat_uc));

    auto get_chat_list_uc =
        std::make_unique<use_case::GetChatListUC>(session_control, db, db);
    auto get_chat_list_handler =
        std::make_unique<controller::GetChatListHandler<json::JsonParser>>(
            std::move(get_chat_list_uc));

    auto add_to_dataset_uc = std::make_unique<use_case::AddToDatasetUC>(
        session_control, adder_dataset);
    auto add_to_dataset_handler =
        std::make_unique<controller::AddToDatasetHandler<json::JsonParser>>(
            std::move(add_to_dataset_uc));

    auto user_logout_uc =
        std::make_unique<use_case::UserLogoutUC>(session_control);
    auto user_logout_handler =
        std::make_unique<controller::UserLogoutHandler<json::JsonParser>>(
            std::move(user_logout_uc));

    auto server_controller = std::make_unique<controller::Controller>();

    server_controller->RegisterHandler("/auth", std::move(user_auth_handler));
    server_controller->RegisterHandler("/chat/list",
                                       std::move(get_chat_list_handler));
    server_controller->RegisterHandler("/chat/update",
                                       std::move(update_chat_handler));
    server_controller->RegisterHandler("/chat/send",
                                       std::move(send_msg_handler));
    server_controller->RegisterHandler("/chat/add",
                                       std::move(add_chat_handler));
    server_controller->RegisterHandler("/chat/ml",
                                       std::move(add_to_dataset_handler));
    server_controller->RegisterHandler("/logout",
                                       std::move(user_logout_handler));

    std::make_unique<
        calmgram::api_server::libs::boost::server::AsyncHttpServer>(
        host, std::stoi(port), std::move(server_controller))
        ->Run();
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return;
  }
}

}  // namespace calmgram::api_server::server