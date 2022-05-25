#ifndef CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_HPP
#define CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_HPP

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

#include <memory>

namespace calmgram::api_server::controller {

template <parser_class Parser>
class UserAuthHandler : public IHandler {
 public:
  UserAuthHandler(std::unique_ptr<use_case::IUserAuthUC>&& use_case)
      : use_case_(std::move(use_case)) {}

  ~UserAuthHandler() = default;

  Response Handle(IRequest const& request) override;

 private:
  std::unique_ptr<use_case::IUserAuthUC> use_case_;
};

template <parser_class Parser>
Response UserAuthHandler<Parser>::Handle(IRequest const& request) {
  if (request.get_type() != IRequest::POST) {
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  try {
    auto body = Parser(request.get_body());

    auto login = body.template GetValue<std::string>(body_fields::kLogin);
    auto password = body.template GetValue<std::string>(body_fields::kPassword);

    std::string token = use_case_->Execute(login, password);

    body.Refresh();
    body.SetValue(body_fields::kToken, token);

    return {Response::OK, body.GetString()};
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_HPP