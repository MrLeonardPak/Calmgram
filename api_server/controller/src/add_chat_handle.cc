#include "add_chat_handler.h"

namespace calmgram::api_server::controller {

AddChatHandler::AddChatHandler(
    std::shared_ptr<use_case::ICheckUser> checker_user,
    std::shared_ptr<use_case::ICreateChat> creater_chat,
    std::shared_ptr<use_case::ISetChat> setter_chat)
    : use_case_(use_case::AddChatUC(checker_user, creater_chat, setter_chat)) {}

Response AddChatHandler::Execute(Request const& request) {
  std::unordered_map<std::string, std::string> params = request.get_params();

  try {
    std::vector<int> users;
    users.push_back(std::stoi(params["user_id_1"]));
    users.push_back(std::stoi(params["user_id_2"]));
    int chat_id = use_case_.Execute(users);
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
