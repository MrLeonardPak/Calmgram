#include "send_msg_handler.h"

namespace calmgram::api_server::controller {

SendMsgHandler::SendMsgHandler(
    std::shared_ptr<use_case::ICheckUser> checker_user,
    std::shared_ptr<use_case::IAnalysisText> analyser_text,
    std::shared_ptr<use_case::ISendMsg> sender_msg)
    : use_case_(use_case::SendMsgUC(checker_user, analyser_text, sender_msg)) {}

Response SendMsgHandler::Execute(Request const& request) {
  std::unordered_map<std::string, std::string> params = request.get_params();

  try {
    int user_id = std::stoi(params["user_id"]);
    int chat_id = std::stoi(params["chat_id"]);
    time_t from_time = std::stol(params["from_time"]);
    entities::Content content;
    if (params["type"] == "text") {
      content.type = entities::TEXT;
    } else if ((params["type"] == "jpeg") || (params["type"] == "jpg")) {
      content.type = entities::JPEG;
    } else {
      throw std::logic_error("Content-Type error");
    }
    content.data = params["data"];
    use_case_.Execute(user_id, chat_id, content);
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
