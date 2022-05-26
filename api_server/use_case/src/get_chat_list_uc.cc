#include "get_chat_list_uc.h"

#include <stdexcept>

namespace calmgram::api_server::use_case {

std::vector<entities::Chat> GetChatListUC::Execute(std::string_view token) {
  std::string user_login = getter_session_login_->GetSessionLogin(token);
  if (user_login.empty()) {
    throw std::runtime_error("Timeout token = " +
                             static_cast<std::string>(token));
  }

  std::vector<int> chat_ids = getter_chat_list_->GetChatList(user_login);
  auto chats = std::vector<entities::Chat>(chat_ids.size());
  for (size_t i = 0; i < chat_ids.size(); ++i) {
    chats[i].id = chat_ids[i];
    chats[i].user_logins = getter_user_list_->GetUserListFromChat(chat_ids[i]);
    chats[i].user_logins.erase(std::find(
        chats[i].user_logins.begin(), chats[i].user_logins.end(), user_login));
  }

  return chats;
}

}  // namespace calmgram::api_server::use_case
