#ifndef CALMGRAM_API_SERVER_USE_CASE_UPDATE_CHAT_H
#define CALMGRAM_API_SERVER_USE_CASE_UPDATE_CHAT_H

#include "interfaces_use_case.h"

#include <memory>
#include <vector>

namespace calmgram::api_server::use_case {

class UpdateChatUC {
 private:
  std::shared_ptr<const ICheckUser> checker_user_;
  std::shared_ptr<const IGetMsgs> getter_msgs_;

 public:
  UpdateChatUC(std::shared_ptr<const ICheckUser> checker_user,
               std::shared_ptr<const IGetMsgs> getter_msgs)
      : checker_user_(checker_user), getter_msgs_(getter_msgs) {}
  ~UpdateChatUC() {}

  std::vector<entities::Message> Execute(int user_id,
                                         int chat_id,
                                         time_t from_time);
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_UPDATE_CHAT_H