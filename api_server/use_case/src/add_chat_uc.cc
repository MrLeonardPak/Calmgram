#include "add_chat_uc.h"

namespace calmgram::api_server::use_case {

int AddChatUC::Execute(std::string_view token,
                       std::vector<std::string_view> const& user_logins) {
  std::string_view user_login = getter_session_login_->GetSessionLogin(token);
  if (user_login.empty()) {
    throw std::runtime_error("Timeout token = " +
                             static_cast<std::string>(token));
  }

  for (auto login : user_logins) {
    if (checker_user_->CheckUser(login)) {
      throw std::runtime_error("No user with login = " +
                               static_cast<std::string>(login));
    }
  }

  auto all_users = std::vector<std::string_view>(user_logins);
  all_users.push_back(user_login);

  int chat_id = creater_chat_->CreateChat(all_users);

  return chat_id;
}

}  // namespace calmgram::api_server::use_case
