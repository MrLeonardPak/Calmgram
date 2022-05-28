#ifndef CALMGRAM_API_SERVER_USE_CASE_USER_LOGOUT_H
#define CALMGRAM_API_SERVER_USE_CASE_USER_LOGOUT_H

#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <memory>

namespace calmgram::api_server::use_case {

class UserLogoutUC : public IUserLogoutUC {
 private:
  std::shared_ptr<IDeleteSession> deleter_session_;

 public:
  UserLogoutUC(std::shared_ptr<IDeleteSession> deleter_session)
      : deleter_session_(deleter_session) {}
  ~UserLogoutUC() = default;

  void Execute(std::string_view token) override;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_USER_LOGOUT_H