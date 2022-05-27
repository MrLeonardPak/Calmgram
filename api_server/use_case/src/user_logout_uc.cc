#include "user_logout_uc.h"

namespace calmgram::api_server::use_case {

void UserLogoutUC::Execute(std::string_view token) {
  deleter_session_->DeleteSession(token);
}

}  // namespace calmgram::api_server::use_case
