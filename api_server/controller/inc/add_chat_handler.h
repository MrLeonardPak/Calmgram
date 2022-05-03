#ifndef CALMGRAM_API_SERVER_CONTROLLER_ADD_CHAT_H
#define CALMGRAM_API_SERVER_CONTROLLER_ADD_CHAT_H

#include "add_chat_uc.h"
#include "interfaces_controller.h"

#include <memory>

namespace calmgram::api_server::controller {

class AddChatHandler : public IHandler {
 private:
  calmgram::api_server::use_case::AddChatUC use_case_;

 public:
  AddChatHandler(std::shared_ptr<use_case::ICheckUser> checker_user,
                 std::shared_ptr<use_case::ICreateChat> creater_chat,
                 std::shared_ptr<use_case::ISetChat> setter_chat);
  ~AddChatHandler() = default;

  Response Execute(Request const& request) override;
};

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_ADD_CHAT_H