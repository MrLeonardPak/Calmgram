#include <iostream>
#include <QApplication>

#include "core.h"

#include "add_chat_handler.h"
#include "auth_handler.h"
#include "send_msg_handler.h"
#include "update_chat_handler.h"
#include "report_handler.h"
#include "update_chats_handler.h"
#include "user_uc.h"
#include "calmgram_window.h"

#include "add_chat.h"
#include "auth.h"
#include "send_msg.h"
#include "update_chat.h"
#include "report.h"
#include "update_chats.h"

namespace calmgram::api_client::client_core {

  void Core::run(int argc, char *argv[]) {
    if ( argc == 1) {
        std::cout << "no args, pls add -local or -window" << std::endl;
        return;
    }
    std::string arg(argv[1]);
    if (arg == "-window") {
      auto auth_handler = std::make_shared<network::AuthorisationHandler>();
      auto update_chats_handler = std::make_shared<network::UpdateChatsHandler>();
      auto update_chat_handler = std::make_shared<network::UpdateChatHandler>();
      auto send_msg_handler = std::make_shared<network::SendMessageHandler>();
      auto add_chat_handler = std::make_shared<network::AddChatHandler>();
      auto report_handler = std::make_shared<network::ReportHandler>();

      auto user_uc = std::make_shared<use_case::UserUseCase>(auth_handler, update_chats_handler,
          update_chat_handler, send_msg_handler, add_chat_handler, report_handler);
      QApplication a(argc, argv);
      user_interface::CalmgramWindow w(user_uc);
      w.show();

      a.exec();
    } else if (arg == "-local") {
      auto auth_handler = std::make_shared<local::AuthorisationHandler>();
      auto update_chats_handler = std::make_shared<local::UpdateChatsHandler>();
      auto update_chat_handler = std::make_shared<local::UpdateChatHandler>();
      auto send_msg_handler = std::make_shared<local::SendMessageHandler>();
      auto add_chat_handler = std::make_shared<local::AddChatHandler>();
      auto report_handler = std::make_shared<local::ReportHandler>();

      auto user_uc = std::make_shared<use_case::UserUseCase>(auth_handler, update_chats_handler,
          update_chat_handler, send_msg_handler, add_chat_handler, report_handler);
      QApplication a(argc, argv);
      user_interface::CalmgramWindow w(user_uc);
      w.show();

      a.exec(); 
    } else {
        std::cout << "wrong args, pls use -local or -window" << std::endl;
    }

  }

}  // namespace calmgram::api_client::core
