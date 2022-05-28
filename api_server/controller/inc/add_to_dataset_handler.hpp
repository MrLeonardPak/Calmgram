#ifndef CALMGRAM_API_SERVER_CONTROLLER_ADD_TO_DATASET_H
#define CALMGRAM_API_SERVER_CONTROLLER_ADD_TO_DATASET_H

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

#include <memory>

namespace calmgram::api_server::controller {

template <parser_class Parser>
class AddToDatasetHandler : public IHandler {
 public:
  AddToDatasetHandler(std::unique_ptr<use_case::IAddToDatasetUC>&& use_case)
      : use_case_(std::move(use_case)) {}

  ~AddToDatasetHandler() = default;

  Response Handle(IRequest const& request) override;

 private:
  std::unique_ptr<use_case::IAddToDatasetUC> use_case_;
};

template <parser_class Parser>
Response AddToDatasetHandler<Parser>::Handle(IRequest const& request) {
  if (request.get_type() != IRequest::POST) {
    Response bad_response(Response::WRONG_TYPE, {});
    return bad_response;
  }

  try {
    auto body = Parser(request.get_body());

    auto token = body.template GetValue<std::string>(body_fields::kToken);
    auto text = body.template GetValue<std::string>(body_fields::kText);
    auto is_marked = body.template GetValue<bool>(body_fields::kIsMarked);

    use_case_->Execute(token, text, is_marked);

    return {Response::OK, {}};
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return {Response::ERROR_DATA, {}};
  }
}

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_ADD_TO_DATASET_H