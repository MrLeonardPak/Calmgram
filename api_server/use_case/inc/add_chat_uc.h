#ifndef CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H
#define CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H

#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <memory>

namespace calmgram::api_server::use_case {

class AddChatUC : public IAddChatUC {
 private:
  std::shared_ptr<IGetSessionLogin const> getter_session_login_;
  std::shared_ptr<ICheckUser const> checker_user_;
  std::shared_ptr<ICreateChat const> creater_chat_;

 public:
  AddChatUC(std::shared_ptr<IGetSessionLogin const> getter_session_login,
            std::shared_ptr<ICheckUser const> checker_user,
            std::shared_ptr<ICreateChat const> creater_chat)
      : getter_session_login_(getter_session_login),
        checker_user_(checker_user),
        creater_chat_(creater_chat) {}
  ~AddChatUC() {}

  int Execute(std::string_view token,
              std::vector<std::string_view> const& user_logins) override;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_ADD_CHAT_H