#include "async_http_server.h"

namespace calmgram::api_server::libs::boost::server {

AsyncHttpServer::AsyncHttpServer(
    std::string const& address,
    unsigned short const& port,
    std::unique_ptr<controller::Controller>&& server_controller,
    size_t thread_pool_size)
    : thread_pool_size_(thread_pool_size),
      ioc_(thread_pool_size),
      listener_(std::make_shared<Listener>(
          ioc_,
          // Create a listening port
          impl::tcp::endpoint{impl::net::ip::make_address(address), port},
          std::move(server_controller))) {}

void AsyncHttpServer::Run() {
  // Launch a listening port
  listener_->Run();
  // Run the I/O service on the requested number of threads
  auto threads = std::vector<std::thread>(thread_pool_size_ - 1);
  auto& ioc = ioc_;
  for (size_t i = 0; i < thread_pool_size_ - 1; ++i) {
    threads.emplace_back([&ioc] { ioc.run(); });
  }
  ioc_.run();
}

}  // namespace calmgram::api_server::libs::boost::server