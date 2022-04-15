#ifndef CALMGRAM_API_SERVER_ROUTER_INTERFACES_H
#define CALMGRAM_API_SERVER_ROUTER_INTERFACES_H

#include <string>

namespace calmgram::api_server::router {

namespace use_case = ::calmgram::api_server::use_case;

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