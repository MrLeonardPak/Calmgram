#ifndef API_CLIENT_IMAGE_CONVERTER_H
#define API_CLIENT_IMAGE_CONVERTER_H

#include "structs.h"

#include <string>

namespace calmgram::api_client::converters {

    class GetImageConverter {
    private:
        network::Request request_;
        std::string client_url_;

    public:
        GetImageConverter() = default;
        ~GetImageConverter() = default;

        bool DataToRequest(std::string server_url);
        bool ResponseToData(network::Response response);
        network::Request GetRequest() {return request_; }
        std::string GetData() { return client_url_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_IMAGE_CONVERTER_H
