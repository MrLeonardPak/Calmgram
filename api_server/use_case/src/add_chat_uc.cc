#include "add_chat_uc.h"
#include <iostream>

#include <stdexcept>

namespace calmgram::api_server::use_case {

int AddChatUC::Execute(std::vector<int> users) {
  // Может вызвать исключения, обрабатываются вызывающим
  for (auto const& user : users) {
    checker_user_->CheckUser(user);
  }

  int chat_id(creater_chat_->CreateChat());
  setter_chat_->SetChat(users, chat_id);

  return chat_id;
}

}  // namespace calmgram::api_server::use_case
