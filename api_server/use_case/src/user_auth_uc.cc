#include "user_auth_uc.h"

#include <cstring>

namespace calmgram::api_server::use_case {

std::string UserAuthUC::Execute(std::string_view login,
                                std::string_view password) {
  // Булевые операции выполняются лениво
  if (checker_user_->CheckUser(login, password) == false &&
      creater_user_->CreateUser(login, password) == false) {
    throw std::runtime_error(
        "Incorrect login (" + static_cast<std::string>(login) +
        ") or password (" + static_cast<std::string>(password) + ")");
  }

  return creater_session_->CreateSession(login);
}

}  // namespace calmgram::api_server::use_case
