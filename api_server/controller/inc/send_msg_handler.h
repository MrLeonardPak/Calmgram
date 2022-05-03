#ifndef CALMGRAM_API_SERVER_CONTROLLER_SEND_MSG_H
#define CALMGRAM_API_SERVER_CONTROLLER_SEND_MSG_H

#include "interfaces_controller.h"
#include "send_msg_uc.h"

#include <memory>

namespace calmgram::api_server::controller {

class SendMsgHandler : public IHandler {
 private:
  calmgram::api_server::use_case::SendMsgUC use_case_;

 public:
  SendMsgHandler(std::shared_ptr<use_case::ICheckUser> checker_user,
                 std::shared_ptr<use_case::IAnalysisText> analyser_text,
                 std::shared_ptr<use_case::ISendMsg> sender_msg);
  ~SendMsgHandler() = default;

  Response Execute(Request const& request) override;
};

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_SEND_MSG_H