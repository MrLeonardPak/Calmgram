#ifndef CALMGRAM_API_SERVER_USE_CASE_UPDATE_CHAT_H
#define CALMGRAM_API_SERVER_USE_CASE_UPDATE_CHAT_H

#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <memory>

namespace calmgram::api_server::use_case {

class UpdateChatUC : public IUpdateChatUC {
 private:
  std::shared_ptr<IGetSessionLogin> getter_session_login_;
  std::shared_ptr<ICheckUserAccessToChat const> checker_user_access_;
  std::shared_ptr<IGetMsgs const> getter_msgs_;

 public:
  UpdateChatUC(
      std::shared_ptr<IGetSessionLogin> getter_session_login,
      std::shared_ptr<ICheckUserAccessToChat const> checker_user_access,
      std::shared_ptr<IGetMsgs const> getter_msgs)
      : getter_session_login_(getter_session_login),
        checker_user_access_(checker_user_access),
        getter_msgs_(getter_msgs) {}
  ~UpdateChatUC() = default;

  std::vector<entities::Message> Execute(std::string_view token,
                                         int chat_id,
                                         time_t from_time) override;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_UPDATE_CHAT_H