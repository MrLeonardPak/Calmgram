#ifndef API_CLIENT_REQUEST_SENDER_H
#define API_CLIENT_REQUEST_SENDER_H

#include "structs.h"

namespace calmgram::api_client::network {

    class RequestSender {
    public:
        RequestSender() = default;
        ~RequestSender() = default;

        Response Execute(Request request);
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_REQUEST_SENDER_H
