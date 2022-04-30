#ifndef CALMGRAM_API_SERVER_ROUTER_USER_AUTH_H
#define CALMGRAM_API_SERVER_ROUTER_USER_AUTH_H

#include "interfaces_router.h"
#include "user_auth_uc.h"

namespace calmgram::api_server::router {

class UserAuthHandler : public IHandler {
 private:
  calmgram::api_server::use_case::UserAuthUC* use_case_;

 public:
  //  TODO: При создании обработчика, он сам создает UseCase, а перед каждым
  //  стартом сценария сам выставляет его состояние (заполняет поля)
  UserAuthHandler() {}
  ~UserAuthHandler() {}

  bool ShouldExecute(Request const& request) override;
  Response Execute(Request const& request) override;
};

}  // namespace calmgram::api_server::router

#endif  // CALMGRAM_API_SERVER_ROUTER_USER_AUTH_H