#ifndef CALMGRAM_API_SERVER_CONTROLLER_USER_LOGOUT_HPP
#define CALMGRAM_API_SERVER_CONTROLLER_USER_LOGOUT_HPP

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

#include <memory>

namespace calmgram::api_server::controller {

template <parser_class Parser>
class UserLogoutHandler : public IHandler {
 public:
  UserLogoutHandler(std::unique_ptr<use_case::IUserLogoutUC>&& use_case)
      : use_case_(std::move(use_case)) {}

  ~UserLogoutHandler() = default;

  Response Handle(IRequest const& request) override;

 private:
  std::unique_ptr<use_case::IUserLogoutUC> use_case_;
};

template <parser_class Parser>
Response UserLogoutHandler<Parser>::Handle(IRequest const& request) {
  if (request.get_type() != IRequest::POST) {
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  try {
    auto body = Parser(request.get_body());

    auto token = body.template GetValue<std::string>(body_fields::kToken);

    use_case_->Execute(token);

    return {Response::OK, {}};
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << std::endl;
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_USER_LOGOUT_HPP