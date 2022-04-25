#ifndef API_CLIENT_AUTH_CONVERTER_H
#define API_CLIENT_AUTH_CONVERTER_H

#include "structs.h"

#include <vector>

namespace calmgram::api_client::converters {

    class AuthorisationConverter {
    private:
        network::Request request_;
        std::vector<int> chat_id_;

    public:
        AuthorisationConverter() = default;
        ~AuthorisationConverter() = default;

        bool DataToRequest(int id);
        bool ResponseToData(network::Response response);
        network::Request GetRequest() { return request_; }
        std::vector<int> GetData() { return chat_id_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_AUTH_CONVERTER_H
