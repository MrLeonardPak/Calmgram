#ifndef API_CLIENT_IMAGE_CONVERTER_H
#define API_CLIENT_IMAGE_CONVERTER_H

#include <string>

namespace calmgram::api_client::converters {

    class GetImageConverter {
    private:
        std::string request_;
        std::string client_url_;

    public:
        GetImageConverter() = default;
        ~GetImageConverter() = default;

        bool DataToRequest(std::string server_url);
        bool ResponseToData(std::string response);
        std::string GetRequest() {return request_; }
        std::string GetData() { return client_url_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_IMAGE_CONVERTER_H
