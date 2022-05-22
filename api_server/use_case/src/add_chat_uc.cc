#include "add_chat_uc.h"
#include <iostream>

#include <stdexcept>

namespace calmgram::api_server::use_case {

int AddChatUC::Execute(std::vector<int> users) {
  for (auto const& user : users) {
    if (!checker_user_->CheckUserExist(user)) {
      throw std::out_of_range("Not user with id = " + std::to_string(user));
    }
  }

  int chat_id(creater_chat_->CreateChat());
  setter_chat_->SetChat(users, chat_id);

  return chat_id;
}

}  // namespace calmgram::api_server::use_case
