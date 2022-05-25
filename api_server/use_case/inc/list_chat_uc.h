#ifndef CALMGRAM_API_SERVER_USE_CASE_LIST_CHAT_H
#define CALMGRAM_API_SERVER_USE_CASE_LIST_CHAT_H

#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <memory>

namespace calmgram::api_server::use_case {

class ListChatUC : public IListChatUC {
 private:
  std::shared_ptr<IGetSessionLogin const> getter_session_login_;
  std::shared_ptr<IGetChatList const> getter_chat_list_;

 public:
  ListChatUC(std::shared_ptr<IGetSessionLogin const> getter_session_login,
             std::shared_ptr<IGetChatList const> getter_chat_list)
      : getter_session_login_(getter_session_login),
        getter_chat_list_(getter_chat_list) {}
  ~ListChatUC() = default;

  std::vector<int> Execute(std::string_view token) override;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_LIST_CHAT_H