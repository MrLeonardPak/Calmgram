#include "update_chat_uc.h"

namespace calmgram::api_server::use_case {

std::vector<entities::Message> UpdateChatUC::Execute() {
  checker_user_.CheckUser(user_id_);

  std::vector<entities::Message> msgs =
      getter_msgs_.GetMsgs(chat_id_, from_time_);

  return msgs;
}

}  // namespace calmgram::api_server::use_case
