#ifndef API_CLIENT_STRUCTS_H
#define API_CLIENT_STRUCTS_H

#include <string>

namespace calmgram::api_client::network {

    struct Request {
        std::string body;
    };

    struct Response {
        std::string body;
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_STRUCTS_H
