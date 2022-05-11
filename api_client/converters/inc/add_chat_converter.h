#ifndef API_CLIENT_ADD_CHAT_CONVERTER_H
#define API_CLIENT_ADD_CHAT_CONVERTER_H

#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::converters {

    class AddChatConverter {
    private:
        std::string request_;
        int chat_id_;
    public:
        AddChatConverter() = default;
        ~AddChatConverter() = default;

        bool DataToRequest(int* ids, int n);
        bool ResponseToData(std::string response);
        std::string GetRequest() { return request_; }
        int GetData() { return chat_id_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_ADD_CHAT_CONVERTER_H
