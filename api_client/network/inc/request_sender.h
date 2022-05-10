#ifndef API_CLIENT_REQUEST_SENDER_H
#define API_CLIENT_REQUEST_SENDER_H

#include <string>
#include <boost/asio.hpp>

namespace calmgram::api_client::network {

    class RequestSender {
    public:
        RequestSender() = default;
        ~RequestSender() = default;

        std::string Execute(std::string request);
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_REQUEST_SENDER_H
