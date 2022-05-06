#ifndef CALMGRAM_API_SERVER_CONTROLLER_H
#define CALMGRAM_API_SERVER_CONTROLLER_H

#include "interfaces_controller.h"

#include <memory>
#include <unordered_map>

namespace calmgram::api_server::controller {

class Controller {
 private:
  std::unordered_map<std::string, std::unique_ptr<IHandler>> router_;

 public:
  Controller();
  ~Controller();

  void RegisterHandler(std::string url, std::unique_ptr<IHandler> handler);
  Response ExecuteHandler(Request const& request);
};

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_H