#ifndef CALMGRAM_API_SERVER_LIBS_BOOST_SERVER_LISTENER_H
#define CALMGRAM_API_SERVER_LIBS_BOOST_SERVER_LISTENER_H

#include "session.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <memory>

namespace calmgram::api_server::libs::boost::server {

namespace impl {

namespace net = ::boost::asio;
namespace beast = ::boost::beast;
using tcp = net::ip::tcp;

}  // namespace impl

// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener> {
 public:
  Listener(impl::net::io_context& ioc,
           impl::tcp::endpoint endpoint,
           std::unique_ptr<controller::Controller>&& server_controller);

  // Start accepting incoming connections
  void Run();

 private:
  impl::net::io_context& ioc_;
  impl::tcp::acceptor acceptor_;
  std::shared_ptr<controller::Controller> server_controller_;

  void DoAccept();

  void OnAccept(impl::beast::error_code ec, impl::tcp::socket socket);
};

}  // namespace calmgram::api_server::libs::boost::server

#endif  // CALMGRAM_API_SERVER_LIBS_BOOST_SERVER_LISTENER_H