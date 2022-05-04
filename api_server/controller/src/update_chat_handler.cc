#include "update_chat_handler.h"

namespace calmgram::api_server::controller {

UpdateChatHandler::UpdateChatHandler(
    std::shared_ptr<use_case::ICheckUser> checker_user,
    std::shared_ptr<use_case::IGetMsgs> getter_msgs)
    : use_case_(use_case::UpdateChatUC(checker_user, getter_msgs)){};

Response UpdateChatHandler::Execute(Request const& request) {
  std::unordered_map<std::string, std::string> params = request.get_params();

  try {
    int user_id = std::stoi(params["user_id"]);
    int chat_id = std::stoi(params["chat_id"]);
    time_t from_time = std::stol(params["from_time"]);
    std::vector<entities::Message> msgs =
        use_case_.Execute(user_id, chat_id, from_time);
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
