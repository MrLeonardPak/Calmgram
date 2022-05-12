#include <iostream>
// #include <QApplication>

#include "core.h"

#include "add_chat_handler.h"
#include "auth_handler.h"
#include "send_msg_handler.h"
#include "update_chat_handler.h"

namespace calmgram::api_client::core {

int Core::run(int argc, char* argv[]) {
  auto update_chat_handler = std::make_shared<network::UpdateChatHandler>();
  auto send_msg_handler = std::make_shared<network::SendMessageHandler>();
  auto add_chat_handler = std::make_shared<network::AddChatHandler>();
  auto auth_handler = std::make_shared<network::AuthorisationHandler>();

  auto user_uc = std::make_shared<use_case::UserUseCase>(
      update_chat_handler, send_msg_handler, add_chat_handler, auth_handler);
  // QApplication a(argc, argv);
  // user_interface::CalmgramWindow w(user_uc);
  // w.show();

  // return a.exec();

  // временный код, до подключения qt
  if (argv[argc - 1][0] == '0') {
    return 0;
  }
  return 1;
}

void Core::consol_run() {
  int id;
  int chat_id = 0;
  int buff_id;
  use_case::UserUseCase user(std::make_shared<network::UpdateChatHandler>(),
                             std::make_shared<network::SendMessageHandler>(),
                             std::make_shared<network::AddChatHandler>(),
                             std::make_shared<network::AuthorisationHandler>());

  std::string msg;
  std::cout << "Enter id" << std::endl;
  std::cin >> id;
  user.Auth(id);
  while (true) {
    std::cout << "Enter 1 to get chats " << std::endl;
    std::cout << "Enter 2 to open chat " << std::endl;
    std::cout << "Enter 3 to create chat " << std::endl;
    std::cout << "Enter 4 to send message  " << std::endl;
    std::cout << "Enter 5 to update chats " << std::endl;
    std::cin >> id;
    if (id == 1) {
      std::vector<int> chats = user.GetChats();
      for (size_t i = 0; i < chats.size(); i++) {
        std::cout << chats[i] << ", ";
      }
      std::cout << std::endl;
    } else if (id == 2) {
      std::cout << "Enter chatID to open chat " << std::endl;
      std::cin >> chat_id;
      std::vector<entities::Message> msgs = user.OpenChat(chat_id);
      std::cout << "msgs in chat " << msgs.size() << std::endl;
      for (size_t i = 0; i < msgs.size(); i++) {
        if (msgs[i].is_marked) {
          std::cout << msgs[i].owner_id << ":*censored*" << std::endl;
        } else {
          std::cout << msgs[i].owner_id << ":" << msgs[i].content.data
                    << std::endl;
        }
      }
    } else if (id == 3) {
      std::cout << "Enter userID to create chat with him" << std::endl;
      std::cin >> buff_id;
      if (user.CreateChat(buff_id)) {
        std::cout << "Succes" << std::endl;
      } else {
        std::cout << "Fail" << std::endl;
      }
    } else if (id == 4) {
      std::cout << "write msg" << std::endl;
      std::cin.ignore(1, '\n');
      std::getline(std::cin, msg);
      user.SendMessage(msg, false, chat_id);
    } else if (id == 5) {
      std::vector<int> upd_chats = user.UpdateChats();
      std::vector<int> chats = user.GetChats();
      std::cout << "chats" << std::endl;
      for (size_t i = 0; i < chats.size(); i++) {
        size_t idx = 0;
        bool is_updated = false;
        while (idx < upd_chats.size() && !is_updated) {
          if (upd_chats[idx] == chats[i]) {
            is_updated = true;
          }
          idx++;
        }
        if (!is_updated) {
          std::cout << chats[i] << " ";
        } else {
          std::cout << chats[i] << "(*) ";
        }
      }
      std::cout << std::endl;
    }
  }
}

}  // namespace calmgram::api_client::core