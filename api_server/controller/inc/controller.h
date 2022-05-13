#ifndef CALMGRAM_API_SERVER_CONTROLLER_H
#define CALMGRAM_API_SERVER_CONTROLLER_H

#include "interfaces_controller.h"

#include <memory>
#include <unordered_map>

namespace calmgram::api_server::controller {

class Controller {
 public:
  Controller() = default;
  ~Controller() = default;

  void RegisterHandler(std::string const& url,
                       std::unique_ptr<IHandler>&& handler);
  Response ExecuteHandler(IRequest const& request);

 private:
  std::unordered_map<std::string, std::unique_ptr<IHandler>> router_;
};

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_CONTROLLER_H