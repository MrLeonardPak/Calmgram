#ifndef CALMGRAM_API_SERVER_CONTROLLER_UPDATE_CHAT_HPP
#define CALMGRAM_API_SERVER_CONTROLLER_UPDATE_CHAT_HPP

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

#include <memory>

namespace calmgram::api_server::controller {

namespace impl {

using StructureType = std::unordered_map<std::string, std::any>;

}  // namespace impl

template <parser_class Parser>
class UpdateChatHandler : public IHandler {
 public:
  UpdateChatHandler(std::unique_ptr<use_case::UpdateChatUC>&& use_case)
      : use_case_(std::move(use_case)) {}

  ~UpdateChatHandler() = default;

  Response Handle(Request const& request) override;

 private:
  std::unique_ptr<use_case::IUpdateChatUC> use_case_;

  impl::StructureType MessageToMap(entities::Message msg) {
    return std::unordered_map<std::string, std::any>{
        {"owner_id", msg.owner_id},
        {"owner_id", msg.owner_id},
        {"text", msg.content.text},
        {"is_marked", msg.is_marked}};
  }
};

template <parser_class Parser>
Response UpdateChatHandler<Parser>::Handle(Request const& request) {
  if (request.get_type() != Request::POST) {
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  try {
    auto body = Parser(request.get_body());

    auto user_id = body.template GetValue<int>(body_fields::kUserId);
    auto chat_id = body.template GetValue<int>(body_fields::kChatId);
    auto from_time = body.template GetValue<time_t>(body_fields::kFromTime);
    std::vector<entities::Message> msgs =
        use_case_->Execute(user_id, chat_id, from_time);

    body.Refresh();
    auto msgs_as_map = std::vector<impl::StructureType>();
    for (auto const& msg : msgs) {
      msgs_as_map.push_back(MessageToMap(msg));
    }
    body.SetVector(body_fields::kMsgs, msgs_as_map);

    return {Response::OK, body.GetString()};
  } catch (std::exception const& e) {
    std::cout << e.what() << '\n';
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_UPDATE_CHAT_HPP