#include "send_msg_uc.h"

#include <chrono>

namespace calmgram::api_server::use_case {

void SendMsgUC::Execute(int user_id,
                        int chat_id,
                        entities::Content const& content) {
  if (!checker_user_->CheckUserAccessToChat(user_id, chat_id)) {
    throw std::out_of_range("Not user with id = " + std::to_string(user_id));
  }

  entities::Message msg(
      user_id,
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
      content, false);
  if (!content.text.empty()) {
    msg.is_marked = analizer_text_->AnalysisText(content.text);
  }

  sender_msg_->SendMsg(msg, chat_id);
}

}  // namespace calmgram::api_server::use_case
