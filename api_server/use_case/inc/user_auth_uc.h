#ifndef CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H
#define CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H

#include "interfaces_use_case.h"

#include <memory>
#include <vector>

namespace calmgram::api_server::use_case {

class UserAuthUC {
 private:
  std::shared_ptr<IGetUser> getter_user_;
  std::shared_ptr<ICreateUser> creater_user_;

 public:
  UserAuthUC(std::shared_ptr<IGetUser> getter_user,
             std::shared_ptr<ICreateUser> creater_user)
      : getter_user_(getter_user), creater_user_(creater_user) {}
  ~UserAuthUC() {}

  std::vector<int> Execute(int user_id);
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H