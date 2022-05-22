#include "update_chat_uc.h"

namespace calmgram::api_server::use_case {

std::vector<entities::Message> UpdateChatUC::Execute(int user_id,
                                                     int chat_id,
                                                     time_t from_time) {
  if (!checker_user_->CheckUserAccessToChat(user_id, chat_id)) {
    throw std::out_of_range("Not user with id = " + std::to_string(user_id));
  }

  std::vector<entities::Message> msgs =
      getter_msgs_->GetMsgs(chat_id, from_time);

  return msgs;
}

}  // namespace calmgram::api_server::use_case
