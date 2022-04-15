#ifndef CALMGRAM_API_SERVER_ROUTER_USER_AUTH_H
#define CALMGRAM_API_SERVER_ROUTER_USER_AUTH_H

#include "interfaces_router.h"
#include "user_auth_uc.h"

namespace calmgram::api_server::router {
class UserAuthHandler : public IHandler {
 private:
  use_case::UserAuthUC* use_case_;

 public:
  UserAuthHandler() {}
  ~UserAuthHandler() {}

  bool ShouldExecute(Request const& request) override;
  Response Execute(Request const& request) override;
};
}  // namespace calmgram::api_server::router

#endif  // CALMGRAM_API_SERVER_ROUTER_USER_AUTH_H