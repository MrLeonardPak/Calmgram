#ifndef CALMGRAM_API_SERVER_SESSION_SESSION_CONTROLLER_H
#define CALMGRAM_API_SERVER_SESSION_SESSION_CONTROLLER_H

#include "interfaces_uc_output.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace calmgram::api_server::session {

class SessionController : public use_case::ICreateSession,
                          public use_case::IGetSessionLogin,
                          public use_case::IDeleteSession {
 public:
  SessionController() = default;
  ~SessionController() = default;

  std::string CreateSession(std::string_view user_login) override;
  std::string GetSessionLogin(std::string_view token) const override;
  void DeleteSession(std::string_view token) override;

 private:
  std::unordered_map<std::string, std::string> map_token_;
};

}  // namespace calmgram::api_server::session

#endif  // CALMGRAM_API_SERVER_SESSION_SESSION_CONTROLLER_H