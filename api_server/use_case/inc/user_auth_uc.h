#ifndef CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H
#define CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H

#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <memory>

namespace calmgram::api_server::use_case {

class UserAuthUC : public IUserAuthUC {
 private:
  std::shared_ptr<ICheckUser const> checker_user_;
  std::shared_ptr<ICreateUser const> creater_user_;

  std::shared_ptr<ICreateSession> creater_session_;

 public:
  UserAuthUC(std::shared_ptr<ICheckUser const> checker_user,
             std::shared_ptr<ICreateUser const> creater_user,
             std::shared_ptr<ICreateSession> creater_session)
      : checker_user_(checker_user),
        creater_user_(creater_user),
        creater_session_(creater_session) {}
  ~UserAuthUC() = default;

  std::string Execute(std::string_view login,
                      std::string_view password) override;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H