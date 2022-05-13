#ifndef CALMGRAM_API_SERVER_LIBS_BOOST_SERVER_SESSION_H
#define CALMGRAM_API_SERVER_LIBS_BOOST_SERVER_SESSION_H

#include "controller.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <memory>

namespace calmgram::api_server::libs::boost::server {

namespace impl {

namespace net = ::boost::asio;
namespace beast = ::boost::beast;
namespace http = beast::http;
using tcp = net::ip::tcp;

}  // namespace impl
// Handles an HTTP server connection
class Session : public std::enable_shared_from_this<Session> {
 public:
  Session(impl::tcp::socket&& socket,
          std::shared_ptr<controller::Controller> server_controller);
  // Take ownership of the stream
  void Run();

 private:
  impl::beast::tcp_stream stream_;
  impl::http::request<impl::http::string_body> req_;
  impl::beast::flat_buffer buffer_;
  std::shared_ptr<void> res_;
  std::shared_ptr<controller::Controller> server_controller_;

  void DoRead();
  void OnRead(impl::beast::error_code ec, std::size_t bytes_transferred);
  void OnWrite(bool close,
               impl::beast::error_code ec,
               std::size_t bytes_transferred);
  void DoClose();

  void HandleRequest();
};

}  // namespace calmgram::api_server::libs::boost::server

#endif  // CALMGRAM_API_SERVER_LIBS_BOOST_SERVER_SESSION_H