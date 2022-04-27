#include "add_chat_uc.h"
#include <iostream>

#include <stdexcept>

namespace calmgram::api_server::use_case {

int AddChatUC::Execute() {
  // Может вызвать исключения, обрабатываются вызывающей
  checker_user_.CheckUser(users_[0]);
  checker_user_.CheckUser(users_[1]);

  int chat_id(creater_chat_.CreateChat());
  setter_chat_.SetChat(users_, chat_id);

  return chat_id;
}

}  // namespace calmgram::api_server::use_case
