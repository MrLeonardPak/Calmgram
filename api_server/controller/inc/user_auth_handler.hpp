#ifndef CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_HPP
#define CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_HPP

#include "interfaces_controller.h"

#include <memory>

namespace calmgram::api_server::controller {

template <parser_class Parser>
class UserAuthHandler : public IHandler {
 public:
  UserAuthHandler(std::unique_ptr<use_case::IUserAuthUC>&& use_case)
      : use_case_(std::move(use_case)) {}
  ~UserAuthHandler() = default;

  Response Handle(Request const& request) override;

 private:
  std::unique_ptr<use_case::IUserAuthUC> use_case_;
};

template <parser_class Parser>
Response UserAuthHandler<Parser>::Handle(Request const& request) {
  if (request.get_type() != Request::POST) {
    // TODO: Подготовить ответ об ошибке
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  auto body = Parser(request.get_body());

  try {
    auto user_id = body.template GetValue<int>(constants::kUserId);
    std::vector<int> chats = use_case_->Execute(user_id);
    // TODO: Подготовить ответ с данными
    auto response_body =
        std::unordered_map<std::string, std::any>{{constants::kChats, chats}};
    return {Response::OK, std::move(response_body)};
  } catch (std::exception const& e) {
    std::cout << e.what() << '\n';
    // TODO: Подготовить ответ об ошибке
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_USER_AUTH_HPP