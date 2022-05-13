#ifndef API_CLIENT_AUTH_CONVERTER_H
#define API_CLIENT_AUTH_CONVERTER_H

#include <string>
#include <vector>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::converters {

    class AuthorisationConverter {
    private:
        std::string request_;
        std::vector<int> chat_id_;

    public:
        AuthorisationConverter() = default;
        ~AuthorisationConverter() = default;

        bool DataToRequest(int id);
        bool ResponseToData(std::string response);
        std::string GetRequest() { return request_; }
        std::vector<int> GetData() { return chat_id_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_AUTH_CONVERTER_H
