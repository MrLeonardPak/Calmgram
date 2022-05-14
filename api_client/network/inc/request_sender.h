#ifndef API_CLIENT_REQUEST_SENDER_H
#define API_CLIENT_REQUEST_SENDER_H

#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace calmgram::api_client::network {

    class RequestSender {
    public:
        RequestSender() = default;
        ~RequestSender() = default;

        std::string Execute(std::string request, std::string target, bool is_get);
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_REQUEST_SENDER_H
