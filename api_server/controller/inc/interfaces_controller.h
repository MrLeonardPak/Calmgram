#ifndef CALMGRAM_API_SERVER_INTERFACES_CONTROLLER_H
#define CALMGRAM_API_SERVER_INTERFACES_CONTROLLER_H

#include <string>
#include <tuple>
#include <unordered_map>

namespace calmgram::api_server::controller {

// enum TypeOfUseCase { USER_AUTH, ADD_CHAT, SEND_MSG, UPDATE_CHAT };

// TODO: адаптер над boost`ом

struct Response {
  std::string body;
};

class Request {
 public:
  virtual std::string get_url() const = 0;
  virtual std::unordered_map<std::string, std::string> get_params() const = 0;
};

class IHandler {
 public:
  virtual ~IHandler(){};
  virtual Response Execute(Request const& request) = 0;
};

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_INTERFACES_CONTROLLER_H