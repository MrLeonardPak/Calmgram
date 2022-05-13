#ifndef CALMGRAM_API_SERVER_ROUTER_INTERFACES_H
#define CALMGRAM_API_SERVER_ROUTER_INTERFACES_H

#include <string>
#include "interfaces_use_case.h"

namespace calmgram::api_server::router {

struct Request {
  std::string body;
};

struct Response {
  std::string body;
};

class IHandler {
 public:
  virtual ~IHandler(){};
  virtual bool ShouldExecute(Request const& request) = 0;
  virtual Response Execute(Request const& request) = 0;
};

}  // namespace calmgram::api_server::router

#endif  // CALMGRAM_API_SERVER_ROUTER_INTERFACES_H