#include <iostream>

#include "core.h"

#include "add_chat_handler.h"
#include "auth_handler.h"
#include "send_msg_handler.h"
#include "update_chat_handler.h"

namespace calmgram::api_client::core {

void Core::run() {
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
  
  user.auth(id);
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
      for (size_t i = 0; i < msgs.size(); i++) {
        std::cout << msgs[i].owner_id << ":" << msgs[i].content.data
                  << std::endl;
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
      std::cin >> msg;
      user.SendMessage(msg, false, chat_id);
    } else if (id == 5) {
      std::vector<int> chats = user.UpdateChats();
      std::cout << "updated chats" << std::endl;
      for (size_t i = 0; i < chats.size(); i++) {
        std::cout << chats[i] << " ";
      }
    }
  }
}

}  // namespace calmgram::api_client::core