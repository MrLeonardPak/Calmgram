#ifndef API_CLIENT_REQUEST_SENDER_H
#define API_CLIENT_REQUEST_SENDER_H

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <string>

namespace calmgram::api_client::network {

enum RequestType { GET, POST, CONNECT };
class RequestSender {
 public:
  RequestSender() = default;
  ~RequestSender() = default;

  std::string Execute(std::string request,
                      std::string target,
                      RequestType request_type);
};

}  // namespace calmgram::api_client::network

#endif  // API_CLIENT_REQUEST_SENDER_H
