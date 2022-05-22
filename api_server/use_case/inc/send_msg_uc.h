#ifndef CALMGRAM_API_SERVER_USE_CASE_SEND_MSG_H
#define CALMGRAM_API_SERVER_USE_CASE_SEND_MSG_H

#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <memory>

namespace calmgram::api_server::use_case {

class SendMsgUC : public ISendMsgUC {
 private:
  std::shared_ptr<const ICheckUserAccessToChat> checker_user_;
  std::shared_ptr<const IAnalysisText> analizer_text_;
  std::shared_ptr<const ISendMsg> sender_msg_;

 public:
  SendMsgUC(std::shared_ptr<const ICheckUserAccessToChat> checker_user,
            std::shared_ptr<const IAnalysisText> analizer_text,
            std::shared_ptr<const ISendMsg> sender_msg)
      : checker_user_(checker_user),
        analizer_text_(analizer_text),
        sender_msg_(sender_msg) {}
  ~SendMsgUC() = default;

  void Execute(int user_id,
               int chat_id,
               entities::Content const& content) override;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_SEND_MSG_H