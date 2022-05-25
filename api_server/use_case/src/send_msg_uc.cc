#include "send_msg_uc.h"

namespace calmgram::api_server::use_case {

void SendMsgUC::Execute(std::string_view token,
                        int chat_id,
                        entities::Content const& content) {
  std::string_view user_login = getter_session_login_->GetSessionLogin(token);
  if (user_login.empty()) {
    throw std::runtime_error("Timeout token = " +
                             static_cast<std::string>(token));
  }

  if (!checker_user_->CheckUserAccessToChat(user_login, chat_id)) {
    throw std::runtime_error(
        "User login = " + static_cast<std::string>(user_login) +
        "want to sent message to chat id = " + std::to_string(chat_id));
  }

  entities::Message msg(user_login, time(nullptr), content, false);
  if (!content.text.empty()) {
    msg.is_marked = analizer_text_->AnalysisText(content.text);
  }

  sender_msg_->SendMsg(msg, chat_id);
}

}  // namespace calmgram::api_server::use_case
