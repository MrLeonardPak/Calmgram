#ifndef API_CLIENT_LOGOUT_H
#define API_CLIENT_LOGOUT_H

#include "interfaces_handlers.h"

#include <iostream>

namespace calmgram::api_client::local {

class LogoutHandler : public network::ILogout {
 public:
  LogoutHandler() = default;
  ~LogoutHandler() = default;

  bool Execute(std::string const& token) override {
    std::cout << "token: " << token << std::endl;
    return true;
  }
};

}  // namespace calmgram::api_client::local

#endif  // API_CLIENT_LOGOUT_H