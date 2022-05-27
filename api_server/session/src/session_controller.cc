#include "session_controller.h"

#include <algorithm>
#include <iostream>
#include <random>

namespace calmgram::api_server::session {

std::string SessionController::CreateSession(std::string_view user_login) {
  std::random_device rd;
  std::minstd_rand g(rd());

  bool gen_token = false;
  auto token = std::string();
  while (!gen_token) {
    token = std::string(user_login) + std::to_string(time(nullptr));
    std::ranges::shuffle(token, rd);

    gen_token = map_token_.emplace(token, user_login).second;
  }

  return token;
}

std::string SessionController::GetSessionLogin(std::string_view token) const {
  auto login = std::string();

  if (map_token_.contains(token.data())) {
    login = map_token_.at(token.data());
  }

  return login;
}

void SessionController::DeleteSession(std::string_view token) {
  map_token_.erase(token.data());
}

}  // namespace calmgram::api_server::session