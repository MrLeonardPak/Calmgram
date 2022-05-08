#ifndef CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H
#define CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H

#include "interfaces_input.h"
#include "interfaces_output.h"

#include <memory>
#include <vector>

namespace calmgram::api_server::use_case {

class AddChatUC : public IAddChatUC {
 private:
  std::shared_ptr<const ICheckUser> checker_user_;
  std::shared_ptr<const ICreateChat> creater_chat_;
  std::shared_ptr<const ISetChat> setter_chat_;

 public:
  AddChatUC(std::shared_ptr<const ICheckUser> checker_user,
            std::shared_ptr<const ICreateChat> creater_chat,
            std::shared_ptr<const ISetChat> setter_chat)
      : checker_user_(checker_user),
        creater_chat_(creater_chat),
        setter_chat_(setter_chat) {}
  ~AddChatUC() {}

  int Execute(std::vector<int> users);
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H