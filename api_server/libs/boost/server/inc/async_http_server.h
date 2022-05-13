#ifndef CALMGRAM_API_SERVER_LIBS_BOOST_SERVER_ASYNC_HTTP_SERVER_H
#define CALMGRAM_API_SERVER_LIBS_BOOST_SERVER_ASYNC_HTTP_SERVER_H

#include "listener.h"

#include <sys/sysinfo.h>
#include <string>

namespace calmgram::api_server::libs::boost::server {

class AsyncHttpServer {
 public:
  AsyncHttpServer(std::string const& address,
                  unsigned short const& port,
                  std::unique_ptr<controller::Controller>&& server_controller,
                  size_t thread_pool_size = get_nprocs());

  ~AsyncHttpServer() = default;

  void Run();

 private:
  size_t thread_pool_size_ = {1};
  impl::net::io_context ioc_;
  std::shared_ptr<Listener> listener_;
};

}  // namespace calmgram::api_server::libs::boost::server

#endif  // CALMGRAM_API_SERVER_LIBS_BOOST_SERVER_ASYNC_HTTP_SERVER_H