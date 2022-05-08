#ifndef CALMGRAM_API_SERVER_CONTROLLER_SEND_MSG_H
#define CALMGRAM_API_SERVER_CONTROLLER_SEND_MSG_H

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

#include <memory>

namespace calmgram::api_server::controller {

template <parser_class Parser>
class SendMsgHandler : public IHandler {
 public:
  SendMsgHandler(std::unique_ptr<use_case::ISendMsgUC>&& use_case)
      : use_case_(use_case) {}

  ~SendMsgHandler() = default;

  Response Handle(Request const& request) override;

 private:
  std::unique_ptr<use_case::ISendMsgUC> use_case_;
};

template <parser_class Parser>
Response SendMsgHandler<Parser>::Handle(Request const& request) {
  if (request.get_type() != Request::POST) {
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  try {
    auto body = Parser(request.get_body());

    auto user_id = body.template GetValue<int>(body_fields::kUserId);
    auto chat_id = body.template GetValue<int>(body_fields::kChatId);
    auto text = body.template GetValue<std::string>(body_fields::kText);
    // TODO: Реализовать прием массива байт
    // auto image = body.template GetaArray<std::byte>(body_fields::kImage);
    auto content = entities::Content{.text = text, .type = entities::TEXT};
    use_case_->Execute(user_id, chat_id, content);

    return {Response::OK, {}};
  } catch (std::exception const& e) {
    std::cout << e.what() << '\n';
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_SEND_MSG_H