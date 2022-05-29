#ifndef CALMGRAM_API_SERVER_CONTROLLER_UPDATE_CHAT_HPP
#define CALMGRAM_API_SERVER_CONTROLLER_UPDATE_CHAT_HPP

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

#include <memory>

namespace calmgram::api_server::controller {

template <parser_class Parser>
class UpdateChatHandler : public IHandler {
 public:
  UpdateChatHandler(std::unique_ptr<use_case::IUpdateChatUC>&& use_case)
      : use_case_(std::move(use_case)) {}

  ~UpdateChatHandler() = default;

  Response Handle(IRequest const& request) override;

 private:
  std::unique_ptr<use_case::IUpdateChatUC> use_case_;
};

template <parser_class Parser>
Response UpdateChatHandler<Parser>::Handle(IRequest const& request) {
  if (request.get_type() != IRequest::GET) {
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  try {
    auto body = Parser(request.get_body());

    auto token = body.template GetValue<std::string>(body_fields::kToken);
    auto chat_id = body.template GetValue<int>(body_fields::kChatId);
    auto from_time = body.template GetValue<time_t>(body_fields::kFromTime);

    std::vector<entities::Message> msgs =
        use_case_->Execute(token, chat_id, from_time);

    body.Refresh();
    body.SetVector(body_fields::kMsgs, msgs);

    return {Response::OK, body.GetString()};
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << std::endl;
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_UPDATE_CHAT_HPP