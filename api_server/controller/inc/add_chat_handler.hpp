#ifndef CALMGRAM_API_SERVER_CONTROLLER_ADD_CHAT_H
#define CALMGRAM_API_SERVER_CONTROLLER_ADD_CHAT_H

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

#include <memory>

namespace calmgram::api_server::controller {

template <parser_class Parser>
class AddChatHandler : public IHandler {
 public:
  AddChatHandler(std::unique_ptr<use_case::IAddChatUC>&& use_case)
      : use_case_(std::move(use_case)) {}

  ~AddChatHandler() = default;

  Response Handle(IRequest const& request) override;

 private:
  std::unique_ptr<use_case::IAddChatUC> use_case_;
};

template <parser_class Parser>
Response AddChatHandler<Parser>::Handle(IRequest const& request) {
  if (request.get_type() != IRequest::POST) {
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  try {
    auto body = Parser(request.get_body());

    auto token = body.template GetValue<std::string>(body_fields::kToken);
    auto user_logins =
        body.template GetVector<std::string>(body_fields::kUserLogins);

    auto user_logins_view = std::vector<std::string_view>(user_logins.size());
    for (size_t i = 0; i < user_logins.size(); ++i) {
      user_logins_view[i] = user_logins[i];
    }

    int chat_id = use_case_->Execute(token, user_logins_view);

    body.Refresh();
    body.SetValue(body_fields::kChatId, chat_id);

    return {Response::OK, body.GetString()};
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_ADD_CHAT_H