#ifndef API_CLIENT_LOGOUT_HENDLER_H
#define API_CLIENT_LOGOUT_HENDLER_H

#include "interfaces_handlers.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::network {

class LogoutHandler : public ILogout {
 private:
  std::string request_;

 public:
  LogoutHandler() = default;
  ~LogoutHandler() = default;

  bool Execute(std::string const& token) override;

  bool DataToRequest(std::string const& token);
};

}  // namespace calmgram::api_client::network

#endif  // API_CLIENT_LOGOUT_HENDLER_H