#ifndef CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_H
#define CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_H

#include "interfaces_controller.h"
#include "user_auth_uc.h"

#include <memory>

namespace calmgram::api_server::controller {

class UserAuthHandler : public IHandler {
 private:
  calmgram::api_server::use_case::UserAuthUC use_case_;

 public:
  UserAuthHandler(std::shared_ptr<use_case::IGetUser> getter_user,
                  std::shared_ptr<use_case::ICreateChat> creater_chat);
  ~UserAuthHandler() = default;

  Response Execute(Request const& request) override;
};

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_H