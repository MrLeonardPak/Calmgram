#include "update_chat_uc.h"

namespace calmgram::api_server::use_case {

std::vector<entities::Message> UpdateChatUC::Execute(std::string_view token,
                                                     int chat_id,
                                                     time_t from_time) {
  std::string user_login = getter_session_login_->GetSessionLogin(token);
  if (user_login.empty()) {
    throw std::runtime_error("Timeout token = " +
                             static_cast<std::string>(token));
  }

  if (!checker_user_access_->CheckUserAccessToChat(user_login, chat_id)) {
    throw std::runtime_error(
        "User login = " + static_cast<std::string>(user_login) +
        "want to get messages from chat id = " + std::to_string(chat_id));
  }

  std::vector<entities::Message> msgs =
      getter_msgs_->GetMsgs(chat_id, from_time);

  return msgs;
}

}  // namespace calmgram::api_server::use_case
