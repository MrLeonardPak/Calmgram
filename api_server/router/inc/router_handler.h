#ifndef CALMGRAM_API_SERVER_ROUTER_HANDLER_H
#define CALMGRAM_API_SERVER_ROUTER_HANDLER_H

#include "interfaces_router.h"

#include <vector>

namespace calmgram::api_server::router {
class RouterHandler {
 private:
  std::vector<IHandler> handlers_;

 public:
  RouterHandler() {}
  ~RouterHandler() {}

  void RegisterHandler(IHandler const& handler);
  Response ExecuteHandler(Request const& request);
};
}  // namespace calmgram::api_server::router

#endif  // CALMGRAM_API_SERVER_ROUTER_HANDLER_H