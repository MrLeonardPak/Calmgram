#include <QApplication>
#include <iostream>

#include "core.h"

#include "add_chat_handler.h"
#include "auth_handler.h"
#include "calmgram_window.h"
#include "logout_handler.h"
#include "report_handler.h"
#include "send_msg_handler.h"
#include "update_chat_handler.h"
#include "update_chats_handler.h"
#include "user_uc.h"

namespace calmgram::api_client::client_core {

void Core::run(int argc, char* argv[]) {
  auto auth_handler = std::make_shared<network::AuthorisationHandler>();
  auto update_chats_handler = std::make_shared<network::UpdateChatsHandler>();
  auto update_chat_handler = std::make_shared<network::UpdateChatHandler>();
  auto send_msg_handler = std::make_shared<network::SendMessageHandler>();
  auto add_chat_handler = std::make_shared<network::AddChatHandler>();
  auto report_handler = std::make_shared<network::ReportHandler>();
  auto logout_handler = std::make_shared<network::LogoutHandler>();

  auto user_uc = std::make_shared<use_case::UserUseCase>(
        auth_handler, update_chats_handler, update_chat_handler,
        send_msg_handler, add_chat_handler, report_handler, logout_handler);
  QApplication a(argc, argv);
  user_interface::CalmgramWindow w(user_uc);

  w.show();

  a.exec();
}

}  // namespace calmgram::api_client::client_core
