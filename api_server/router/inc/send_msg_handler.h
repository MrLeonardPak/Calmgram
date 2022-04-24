#ifndef CALMGRAM_API_SERVER_ROUTER_SEND_MSG_H
#define CALMGRAM_API_SERVER_ROUTER_SEND_MSG_H

#include "interfaces_router.h"
#include "send_msg_uc.h"

namespace calmgram::api_server::router {

class SendMsgHandler : public IHandler {
 private:
  calmgram::api_server::use_case::SendMsgUC* use_case_;

 public:
  SendMsgHandler() {}
  ~SendMsgHandler() {}

  bool ShouldExecute(Request const& request) override;
  Response Execute(Request const& request) override;
};

}  // namespace calmgram::api_server::router

#endif  // CALMGRAM_API_SERVER_ROUTER_SEND_MSG_H