#ifndef CALMGRAM_API_SERVER_ROUTER_UPDATE_CHAT_H
#define CALMGRAM_API_SERVER_ROUTER_UPDATE_CHAT_H

#include "interfaces_router.h"
#include "update_chat_uc.h"

namespace calmgram::api_server::router {

class UpdateChatHandler : public IHandler {
 private:
  calmgram::api_server::use_case::UpdateChatUC* use_case_;

 public:
  UpdateChatHandler() {}
  ~UpdateChatHandler() {}

  bool ShouldExecute(Request const& request) override;
  Response Execute(Request const& request) override;
};

}  // namespace calmgram::api_server::router

#endif  // CALMGRAM_API_SERVER_ROUTER_UPDATE_CHAT_H