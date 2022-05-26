#ifndef CALMGRAM_API_SERVER_USE_CASE_ADD_TO_DATASET_H
#define CALMGRAM_API_SERVER_USE_CASE_ADD_TO_DATASET_H

#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <memory>

namespace calmgram::api_server::use_case {

class AddToDatasetUC : public IAddToDatasetUC {
 private:
  std::shared_ptr<IGetSessionLogin> getter_session_login_;
  std::shared_ptr<IAdditionalDataset const> adder_dataset_;

 public:
  AddToDatasetUC(std::shared_ptr<IGetSessionLogin> getter_session_login,
                 std::shared_ptr<IAdditionalDataset const> adder_dataset)
      : getter_session_login_(getter_session_login),
        adder_dataset_(adder_dataset) {}
  ~AddToDatasetUC() {}

  void Execute(std::string_view token,
               std::string_view data,
               bool label) override;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_ADD_TO_DATASET_H