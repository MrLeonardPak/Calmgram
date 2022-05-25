#include "add_to_dataset_uc.h"

namespace calmgram::api_server::use_case {

void AddToDatasetUC::Execute(std::string_view token,
                             std::string_view data,
                             bool label) {
  std::string user_login = getter_session_login_->GetSessionLogin(token);
  if (user_login.empty()) {
    throw std::runtime_error("Timeout token = " +
                             static_cast<std::string>(token));
  }

  adder_dataset_->AdditionalDataset(data, label);
}

}  // namespace calmgram::api_server::use_case
