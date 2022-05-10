#include "request_sender.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

namespace calmgram::api_client::network {

    std::string RequestSender::Execute(std::string request, char const* target, bool is_get) {

        std::string data;
        auto const host = "127.0.0.1";
        auto const port = "80";
        int version = 11;
        net::io_context ioc;

        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        auto const results = resolver.resolve(host, port);
        stream.connect(results);
        http::request<http::string_body> req;
        if (is_get) {
            req.method(http::verb::get);
        } else {
            req.method(http::verb::post);
        }
        req.target(target);
        req.set(http::field::host, host);
        req.version(version);
        req.set(http::field::content_type, "application/json");
        req.body() = request;
        req.prepare_payload();

        http::write(stream, req);

        beast::flat_buffer buffer;
        
        http::response<http::dynamic_body> res;

        http::read(stream, buffer, res);
        data = beast::buffers_to_string(res.body().data());
        return data;
    }

} // namespace calmgram::api_client::network


