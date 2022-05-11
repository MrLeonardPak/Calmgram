#include "user_auth_uc.h"

#include <stdexcept>

namespace calmgram::api_server::use_case {

std::vector<int> UserAuthUC::Execute(int user_id) {
  entities::User user;

  try {
    user = getter_user_->GetUser(user_id);
  } catch (const std::logic_error& le) {
    user = creater_user_->CreateUser(user_id);
  }

  return user.chats;
}

}  // namespace calmgram::api_server::use_case
