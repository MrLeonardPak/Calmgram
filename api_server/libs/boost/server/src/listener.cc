#include "listener.h"

#include <iostream>

namespace calmgram::api_server::libs::boost::server {

// Accepts incoming connections and launches the sessions
Listener::Listener(impl::net::io_context& ioc,
                   impl::tcp::endpoint endpoint,
                   std::unique_ptr<controller::Controller>&& server_controller)
    : ioc_(ioc),
      acceptor_(impl::net::make_strand(ioc)),
      server_controller_(std::move(server_controller)) {
  // Open the acceptor
  acceptor_.open(endpoint.protocol());
  // Allow address reuse
  acceptor_.set_option(impl::net::socket_base::reuse_address(true));
  // Bind to the server address
  acceptor_.bind(endpoint);
  // Start listening for connections
  acceptor_.listen(impl::net::socket_base::max_listen_connections);
}

// Start accepting incoming connections
void Listener::Run() {
  DoAccept();
}

void Listener::DoAccept() {
  // The new connection gets its own strand
  acceptor_.async_accept(
      impl::net::make_strand(ioc_),
      impl::beast::bind_front_handler(&Listener::OnAccept, shared_from_this()));
}

void Listener::OnAccept(impl::beast::error_code ec, impl::tcp::socket socket) {
  if (ec) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << ec.message()
              << std::endl;
    return;  // To avoid infinite loop
  } else {
    // Create the session and run it
    std::make_shared<Session>(std::move(socket), server_controller_)->Run();
  }

  // Accept another connection
  DoAccept();
}

}  // namespace calmgram::api_server::libs::boost::server