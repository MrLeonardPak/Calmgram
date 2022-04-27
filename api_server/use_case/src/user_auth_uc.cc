#include "user_auth_uc.h"
#include <stdexcept>

namespace calmgram::api_server::use_case {

std::vector<int> UserAuthUC::Execute() {
  entities::User user;

  try {
    user = getter_.GetUser(user_id_);
  } catch (const std::logic_error& le) {
    user = creater_.CreateUser(user_id_);
  }

  std::vector<int> chats_id;
  for (auto&& chat : user.chats) {
    chats_id.push_back(chat.id);
  }

  return chats_id;
}

}  // namespace calmgram::api_server::use_case
