#include "get_chat_list_uc.h"

#include <stdexcept>

namespace calmgram::api_server::use_case {

std::vector<int> GetChatListUC::Execute(std::string_view token) {
  std::string_view user_login = getter_session_login_->GetSessionLogin(token);
  if (user_login.empty()) {
    throw std::runtime_error("Timeout token = " +
                             static_cast<std::string>(token));
  }

  return getter_chat_list_->GetChatList(user_login);
}

}  // namespace calmgram::api_server::use_case
