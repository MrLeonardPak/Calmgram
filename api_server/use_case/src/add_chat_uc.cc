#include "add_chat_uc.h"
#include <iostream>

#include <stdexcept>

namespace calmgram::api_server::use_case {

int AddChatUC::Execute(std::vector<int> users) {
  // Может вызвать исключения, обрабатываются вызывающим
  checker_user_->CheckUser(users[0]);
  checker_user_->CheckUser(users[1]);

  int chat_id(creater_chat_->CreateChat());
  setter_chat_->SetChat(users, chat_id);

  return chat_id;
}

}  // namespace calmgram::api_server::use_case
