#ifndef CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H
#define CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H

#include "interfaces_use_case.h"

#include <vector>

namespace calmgram::api_server::use_case {

class UserAuthUC {
 private:
  int user_id_;
  IGetUser& getter_user_;
  ICreateUser& creater_user_;

 public:
  UserAuthUC(int id, IGetUser& getter_user, ICreateUser& creater_user)
      : user_id_(id), getter_user_(getter_user), creater_user_(creater_user) {}
  ~UserAuthUC() {}

  std::vector<int> Execute();
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H