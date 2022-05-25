#ifndef CALMGRAM_API_SERVER_CONTROLLER_GET_CHAT_LIST_HPP
#define CALMGRAM_API_SERVER_CONTROLLER_GET_CHAT_LIST_HPP

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

#include <memory>

namespace calmgram::api_server::controller {

template <parser_class Parser>
class GetChatListHandler : public IHandler {
 public:
  GetChatListHandler(std::unique_ptr<use_case::IGetChatListUC>&& use_case)
      : use_case_(std::move(use_case)) {}

  ~GetChatListHandler() = default;

  Response Handle(IRequest const& request) override;

 private:
  std::unique_ptr<use_case::IUpdateChatUC> use_case_;
};

template <parser_class Parser>
Response GetChatListHandler<Parser>::Handle(IRequest const& request) {
  if (request.get_type() != IRequest::POST) {
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  try {
    auto body = Parser(request.get_body());

    auto token = body.template GetValue<std::string>(body_fields::kToken);

    std::vector<int> chat_ids = use_case_->Execute(token);

    body.Refresh();
    body.SetVector(body_fields::kChatIds, chat_ids);

    return {Response::OK, body.GetString()};
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_GET_CHAT_LIST_HPP