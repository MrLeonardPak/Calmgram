#ifndef CALMGRAM_API_SERVER_SESSION_SESSION_CONTROLLER_H
#define CALMGRAM_API_SERVER_SESSION_SESSION_CONTROLLER_H

#include "interfaces_uc_output.h"

#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std::chrono_literals;

namespace calmgram::api_server::session {

class SessionController : public use_case::ICreateSession,
                          public use_case::IGetSessionLogin {
 public:
  SessionController(std::chrono::minutes timeout) : timeout_(timeout) {}
  ~SessionController() = default;

  void Run();

  std::string CreateSession(std::string_view user_login) override;
  std::string GetSessionLogin(std::string_view token) override;

 private:
  std::unordered_map<
      std::string,
      std::pair<std::string,
                std::chrono::time_point<std::chrono::steady_clock>>>
      map_token_;
  std::chrono::minutes timeout_;

  void CheckSessionTimeout();
};

}  // namespace calmgram::api_server::session

#endif  // CALMGRAM_API_SERVER_SESSION_SESSION_CONTROLLER_H