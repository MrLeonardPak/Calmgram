#ifndef API_CLIENT_SEND_MSG_CONVERTER_H
#define API_CLIENT_SEND_MSG_CONVERTER_H

#include "entities.h"

#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::converters {

    class SendMessageConverter {
    private:
        std::string request_;
        bool is_completed_{};

    public:
        SendMessageConverter() = default;
        ~SendMessageConverter() = default;

        bool DataToRequest(int chat_id, int user_id, entities::Content content);
        bool ResponseToData(std::string response);
        std::string GetRequest() { return request_; }
        bool GetData() {return is_completed_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_SEND_MSG_CONVERTER_H
