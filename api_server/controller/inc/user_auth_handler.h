#ifndef CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_H
#define CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_H

#include "interfaces_controller.h"
#include "user_auth_uc.h"

#include <memory>

namespace calmgram::api_server::controller {

class UserAuthHandler : public IHandler {
 public:
  UserAuthHandler(use_case::UserAuthUC use_case);
  ~UserAuthHandler() = default;

  Response Handle(Request const& request) override;

 private:
  use_case::UserAuthUC use_case_;
};

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_H