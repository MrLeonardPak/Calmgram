#ifndef CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H
#define CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H

#include "interfaces_use_case.h"

#include <vector>

namespace calmgram::api_server::use_case {

class AddChatUC {
 private:
  std::vector<int> users_;
  IGetUser& getter_user_;
  ICreateChat& creater_chat_;
  ISetChat& setter_chat_;

 public:
  AddChatUC(std::vector<int> users,
            IGetUser& getter_user,
            ICreateChat& creater_chat,
            ISetChat& setter_chat)
      : users_(users),
        getter_user_(getter_user),
        creater_chat_(creater_chat),
        setter_chat_(setter_chat) {}
  ~AddChatUC() {}

  int Execute();
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H