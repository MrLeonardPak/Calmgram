#ifndef CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H
#define CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H

#include "interfaces_use_case.h"

#include <vector>

namespace calmgram::api_server::use_case {

class AddChatUC {
 private:
  std::vector<int> users_;
  ISetChat setter_;
  ICreateChat creater_;

 public:
  AddChatUC(std::vector<int> users, ISetChat setter, ICreateChat creater)
      : users_(users), setter_(setter), creater_(creater) {}
  ~AddChatUC() {}

  int Execute();
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H