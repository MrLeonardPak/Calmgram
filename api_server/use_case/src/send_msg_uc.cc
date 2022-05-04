#include "send_msg_uc.h"

#include <chrono>

namespace calmgram::api_server::use_case {

void SendMsgUC::Execute(int user_id,
                        int chat_id,
                        entities::Content const& content) {
  // Может вызвать исключения, обрабатываются вызывающим
  checker_user_->CheckUser(user_id);
  entities::Message msg(
      user_id,
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
      content, false);
  if (content.type == entities::TEXT) {
    msg.is_marked = analizer_text_->AnalysisText(content.data);
  }

  sender_msg_->SendMsg(msg, chat_id);
}

}  // namespace calmgram::api_server::use_case
