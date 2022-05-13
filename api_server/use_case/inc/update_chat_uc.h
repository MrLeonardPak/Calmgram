#ifndef CALMGRAM_API_SERVER_USE_CASE_UPDATE_CHAT_H
#define CALMGRAM_API_SERVER_USE_CASE_UPDATE_CHAT_H

#include "interfaces_use_case.h"

#include <vector>

namespace calmgram::api_server::use_case {

class UpdateChatUC {
 private:
  int user_id_;
  int chat_id_;
  time_t from_time_;
  IGetUser& getter_user_;
  IGetMsgs& getter_msgs_;

 public:
  UpdateChatUC(int user_id,
               int chat_id,
               time_t from_time,
               IGetUser& getter_user,
               IGetMsgs& getter_msgs)
      : user_id_(user_id),
        chat_id_(chat_id),
        from_time_(from_time),
        getter_user_(getter_user),
        getter_msgs_(getter_msgs) {}
  ~UpdateChatUC() {}

  std::vector<entities::Message> Execute();
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_UPDATE_CHAT_H