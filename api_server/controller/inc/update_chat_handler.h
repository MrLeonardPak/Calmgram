#ifndef CALMGRAM_API_SERVER_CONTROLLER_UPDATE_CHAT_H
#define CALMGRAM_API_SERVER_CONTROLLER_UPDATE_CHAT_H

#include "interfaces_controller.h"
#include "update_chat_uc.h"

#include <memory>

namespace calmgram::api_server::controller {

class UpdateChatHandler : public IHandler {
 private:
  calmgram::api_server::use_case::UpdateChatUC use_case_;

 public:
  UpdateChatHandler(std::shared_ptr<use_case::ICheckUser> checker_user,
                    std::shared_ptr<use_case::IGetMsgs> getter_msgs);
  ~UpdateChatHandler() = default;

  Response Execute(Request const& request) override;
};

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_UPDATE_CHAT_H