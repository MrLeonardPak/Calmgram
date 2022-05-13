#include "session.h"

#include <iostream>

namespace calmgram::api_server::libs::boost::server {

class Request : public controller::IRequest {
 public:
  Request(impl::http::request<impl::http::string_body> const& req)
      : req_(req) {}

  std::string get_path() const override { return req_.target().to_string(); }
  RequestType get_type() const override { return RequestType::POST; }
  std::string get_body() const override { return req_.body(); }

 private:
  impl::http::request<impl::http::string_body> req_;
};

// Handles an HTTP server connection
Session::Session(impl::tcp::socket&& socket,
                 std::shared_ptr<controller::Controller> server_controller)
    : stream_(std::move(socket)), server_controller_(server_controller) {}
// Start the asynchronous operation
void Session::Run() {
  // We need to be executing within a strand to perform async operations
  // on the I/O objects in this session. Although not strictly necessary
  // for single-threaded contexts, this example code is written to be
  // thread-safe by default.
  impl::net::dispatch(
      stream_.get_executor(),
      impl::beast::bind_front_handler(&Session::DoRead, shared_from_this()));
}

void Session::DoRead() {
  // Make the request empty before reading,
  // otherwise the operation behavior is undefined.
  req_ = {};

  // Set the timeout.
  stream_.expires_after(std::chrono::seconds(30));

  // Read a request
  impl::http::async_read(
      stream_, buffer_, req_,
      impl::beast::bind_front_handler(&Session::OnRead, shared_from_this()));
}

void Session::OnRead(impl::beast::error_code ec,
                     std::size_t bytes_transferred) {
  ::boost::ignore_unused(bytes_transferred);

  // This means they closed the connection
  if (ec == impl::http::error::end_of_stream)
    return DoClose();

  if (ec) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << ec.message() << '\n';
    return;
  }

  // Send the response
  HandleRequest();
}
void Session::OnWrite(bool close,
                      impl::beast::error_code ec,
                      std::size_t bytes_transferred) {
  ::boost::ignore_unused(bytes_transferred);

  if (ec) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << ec.message() << '\n';
    return;
  }

  if (close) {
    // This means we should close the connection, usually because
    // the response indicated the "Connection: close" semantic.
    return DoClose();
  }

  // We're done with the response so delete it
  // res_ = nullptr;

  // Read another request
  DoRead();
}
void Session::DoClose() {
  // Send a TCP shutdown
  impl::beast::error_code ec;
  stream_.socket().shutdown(impl::tcp::socket::shutdown_send, ec);

  // At this point the connection is closed gracefully
}

void Session::HandleRequest() {
  // TODO: Вызвать контроллер
  auto converted_request = Request(req_);
  controller::Response raw_response =
      server_controller_->ExecuteHandler(converted_request);

  auto response = impl::http::response<impl::http::string_body>(
      impl::http::status::ok, req_.version());
  response.set(impl::http::field::server, BOOST_BEAST_VERSION_STRING);

  switch (raw_response.get_status()) {
    case controller::Response::Status::OK:
      std::cout << "path: " << converted_request.get_path() << std::endl;
      response.result(impl::http::status::ok);
      response.set(impl::http::field::content_type, "application/json");
      response.body() = raw_response.get_body();
      break;
    case controller::Response::Status::NOT_PAGE:
      response.result(impl::http::status::not_found);
      break;
    case controller::Response::Status::ERROR_DATA:
      response.result(impl::http::status::bad_request);
      break;
    case controller::Response::Status::WRONG_TYPE:
      response.result(impl::http::status::bad_request);
      break;
    default:
      response.result(impl::http::status::bad_request);
      break;
  }

  // The lifetime of the message has to extend
  // for the duration of the async operation so
  // we use a shared_ptr to manage it.
  auto sp =
      std::make_shared<impl::http::message<false, impl::http::string_body>>(
          std::move(response));
  // Store a type-erased version of the shared
  // pointer in the class to keep it alive.
  res_ = sp;

  // Write the response
  impl::http::async_write(
      stream_, *sp,
      impl::beast::bind_front_handler(&Session::OnWrite, shared_from_this(),
                                      sp->need_eof()));
}

}  // namespace calmgram::api_server::libs::boost::server