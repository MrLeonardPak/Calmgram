#include "user_auth_handler.h"
#include "json_parser.h"

#include <stdexcept>

namespace calmgram::api_server::controller {

UserAuthHandler::UserAuthHandler(use_case::UserAuthUC use_case)
    : use_case_(use_case) {}

Response UserAuthHandler::Handle(Request const& request) {
  if (request.get_type() != Request::POST) {
    // TODO: Подготовить ответ об ошибке
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  auto body = calmgram::api_server::json::JsonParser(request.get_body());

  try {
    auto user_id = body.GetValue<int>(constants::kUserId, 0);
    std::vector<int> chats = use_case_.Execute(user_id);
    // TODO: Подготовить ответ с данными
    auto response_body =
        std::unordered_map<std::string, std::any>{{constants::kChats, chats}};
    return {Response::OK, response_body};
  } catch (std::exception const& e) {
    std::cout << e.what() << '\n';
    // TODO: Подготовить ответ об ошибке
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller
