#ifndef API_CLIENT_UPDATE_CHAT_CONVERTER_H
#define API_CLIENT_UPDATE_CHAT_CONVERTER_H

#include "entities.h"

#include <vector>
#include <ctime>
#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::converters {

    class UpdateChatConverter {
    private:
        std::string request_;
        std::vector<entities::Message> messages_;

    public:
        UpdateChatConverter() = default;
        ~UpdateChatConverter() = default;

        bool DataToRequest(int user_id, int chat_id, time_t last_update);
        bool ResponseToData(std::string response);
        std::string GetRequest() { return request_; }
        std::vector<entities::Message> GetData() {return messages_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_UPDATE_CHAT_CONVERTER_H
