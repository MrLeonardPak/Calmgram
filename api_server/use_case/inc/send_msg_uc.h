#ifndef CALMGRAM_API_SERVER_USE_CASE_SEND_MSG_H
#define CALMGRAM_API_SERVER_USE_CASE_SEND_MSG_H

#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <memory>

namespace calmgram::api_server::use_case {

class SendMsgUC : public ISendMsgUC {
 private:
  std::shared_ptr<IGetSessionLogin> getter_session_login_;
  std::shared_ptr<ICheckUserAccessToChat const> checker_user_;
  std::shared_ptr<IAnalysisText const> analizer_text_;
  std::shared_ptr<ISendMsg const> sender_msg_;

 public:
  SendMsgUC(std::shared_ptr<IGetSessionLogin> getter_session_login,
            std::shared_ptr<ICheckUserAccessToChat const> checker_user,
            std::shared_ptr<IAnalysisText const> analizer_text,
            std::shared_ptr<ISendMsg const> sender_msg)
      : getter_session_login_(getter_session_login),
        checker_user_(checker_user),
        analizer_text_(analizer_text),
        sender_msg_(sender_msg) {}
  ~SendMsgUC() = default;

  void Execute(std::string_view token,
               int chat_id,
               entities::Content const& content) override;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_SEND_MSG_H