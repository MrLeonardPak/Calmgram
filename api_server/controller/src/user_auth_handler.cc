#include "user_auth_handler.h"

#include <stdexcept>

namespace calmgram::api_server::controller {

UserAuthHandler::UserAuthHandler(
    std::shared_ptr<use_case::IGetUser> getter_user,
    std::shared_ptr<use_case::ICreateUser> creater_user)
    : use_case_(use_case::UserAuthUC(getter_user, creater_user)) {}

Response UserAuthHandler::Execute(Request const& request) {
  std::unordered_map<std::string, std::string> params = request.get_params();

  try {
    int user_id = std::stoi(params["user_id"]);
    std::vector<int> chats = use_case_.Execute(user_id);
  } catch (std::logic_error) {
    // TODO: Подготовить ответ об ошибке
    Response bad;
    return bad;
  }
  // TODO: Подготовить ответ с данными
  Response tmp;
  return tmp;
}

}  // namespace calmgram::api_server::controller
