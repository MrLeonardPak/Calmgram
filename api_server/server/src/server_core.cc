#include "server_core.h"
#include "async_http_server.h"
#include "controller.h"
#include "interfaces_uc_output.h"
#include "json_parser.hpp"

#include "add_chat_handler.hpp"
#include "add_chat_uc.h"

#include "send_msg_handler.hpp"
#include "send_msg_uc.h"

#include "update_chat_handler.hpp"
#include "update_chat_uc.h"

#include "user_auth_handler.hpp"
#include "user_auth_uc.h"

#include "interfaces_uc_input.h"

// #include "nn.h"

#include <iostream>

namespace calmgram::api_server::server {

void ServerCore::Run() {
  auto getter_user = std::make_shared<TestGetUser const>();
  auto creater_user = std::make_shared<TestCreateUser const>();
  auto creater_chat = std::make_shared<TestCreateChat const>();
  auto getter_msgs = std::make_shared<TestGetMsgs const>();
  auto sender_msg = std::make_shared<TestSendMsg const>();
  auto setter_chat = std::make_shared<TestSetChat const>();
  auto checker_user = std::make_shared<TestCheckUser const>();
  auto analyser_text = std::make_shared<TestAnalysisText const>();

  //   auto analyser_text = std::make_shared<calmgram::ml::nn::NN const>();

  auto add_chat_uc = std::make_unique<use_case::AddChatUC>(
      checker_user, creater_chat, setter_chat);
  auto add_chat_handler =
      std::make_unique<controller::AddChatHandler<json::JsonParser>>(
          std::move(add_chat_uc));

  auto send_msg_uc = std::make_unique<use_case::SendMsgUC>(
      checker_user, analyser_text, sender_msg);
  auto send_msg_handler =
      std::make_unique<controller::SendMsgHandler<json::JsonParser>>(
          std::move(send_msg_uc));

  auto update_chat_uc =
      std::make_unique<use_case::UpdateChatUC>(checker_user, getter_msgs);
  auto update_chat_handler =
      std::make_unique<controller::UpdateChatHandler<json::JsonParser>>(
          std::move(update_chat_uc));

  auto user_auth_uc =
      std::make_unique<use_case::UserAuthUC>(getter_user, creater_user);
  auto user_auth_handler =
      std::make_unique<controller::UserAuthHandler<json::JsonParser>>(
          std::move(user_auth_uc));

  auto server_controller = std::make_unique<controller::Controller>();
  auto admin_handler = std::make_unique<AdminHandler>();
  // TODO: Заполнить роутер обработчиками
  server_controller->RegisterHandler("/admin", std::move(admin_handler));
  server_controller->RegisterHandler("/auth", std::move(user_auth_handler));
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
  }
}

}  // namespace calmgram::api_server::server