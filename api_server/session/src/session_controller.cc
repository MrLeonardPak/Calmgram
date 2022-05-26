#include "session_controller.h"

#include <algorithm>
#include <random>

#include <iostream>

namespace calmgram::api_server::session {

void SessionController::Run() {
  while (1) {
    CheckSessionTimeout();
  }
}

void SessionController::CheckSessionTimeout(){
    // auto duration = std::chrono::duration<std::chrono::minutes>();
    // auto now = std::chrono::steady_clock::now();
    // for (auto const& [key, val] : map_token_) {
    //   if (std::chrono::duration_cast<std::chrono::seconds>(val.second - now)
    //   >
    //       timeout_) {
    //     map_token_.extract(key);
    //   }
    // }
};

std::string SessionController::CreateSession(std::string_view user_login) {
  std::random_device rd;
  std::minstd_rand g(rd());

  bool gen_token = false;
  auto token = std::string();
  while (!gen_token) {
    auto cur_time = std::chrono::steady_clock::now();
    token = std::string(user_login) + std::to_string(time(nullptr));
    std::ranges::shuffle(token, rd);

    gen_token =
        map_token_.emplace(token, std::make_pair(user_login, cur_time)).second;
  }

  return token;
}

std::string SessionController::GetSessionLogin(std::string_view token) {
  auto login = std::string();

  if (map_token_.contains(token.data())) {
    login = map_token_.at(token.data()).first;
    map_token_[token.data()].second = std::chrono::steady_clock::now();
  }

  return login;
}

}  // namespace calmgram::api_server::session