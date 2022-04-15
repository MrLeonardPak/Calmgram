#ifndef CALMGRAM_API_SERVER_ROUTER_ADD_CHAT_H
#define CALMGRAM_API_SERVER_ROUTER_ADD_CHAT_H

#include "add_chat_uc.h"
#include "interfaces_router.h"

namespace calmgram::api_server::router {

class AddChatHandler : public IHandler {
 private:
  use_case::AddChatUC* use_case_;

 public:
  AddChatHandler() {}
  ~AddChatHandler() {}

  bool ShouldExecute(Request const& request) override;
  Response Execute(Request const& request) override;
};

}  // namespace calmgram::api_server::router

#endif  // CALMGRAM_API_SERVER_ROUTER_ADD_CHAT_H