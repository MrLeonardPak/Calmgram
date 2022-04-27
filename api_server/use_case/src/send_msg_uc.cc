#include "send_msg_uc.h"

#include <chrono>

namespace calmgram::api_server::use_case {

void SendMsgUC::Execute() {
  // Может вызвать исключения, обрабатываются вызывающим
  checker_user_.CheckUser(user_id_);
  entities::Message msg(
      user_id_,
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
      content_, false);
  if (content_.type == entities::TEXT) {
    msg.is_marked = analizer_text_.AnalysisText(content_.data);
  }

  sender_msg_.SendMsg(msg, chat_id_);
}

}  // namespace calmgram::api_server::use_case
