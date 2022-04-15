#ifndef CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H
#define CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H

#include "interfaces_use_case.h"

#include <vector>

namespace calmgram::api_server::use_case {

class UserAuthUC {
 private:
  int user_id_;
  IGetUser getter_;
  ICreateUser creater_;

 public:
  UserAuthUC(int id, IGetUser getter, ICreateUser creater)
      : user_id_(id), getter_(getter), creater_(creater) {}
  ~UserAuthUC() {}

  std::vector<int> Execute();
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_USER_AUTH_H