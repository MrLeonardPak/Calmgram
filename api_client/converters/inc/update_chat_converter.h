#ifndef API_CLIENT_UPDATE_CHAT_CONVERTER_H
#define API_CLIENT_UPDATE_CHAT_CONVERTER_H

#include "structs.h"
#include "entities.h"

#include <vector>
#include <ctime>

namespace calmgram::api_client::converters {

    class UpdateChatConverter {
    private:
        network::Request request_;
        std::vector<entities::Message> messages_;

    public:
        UpdateChatConverter() = default;
        ~UpdateChatConverter() = default;

        bool DataToRequest(int chat_id, time_t last_update);
        bool ResponseToData(network::Response response);
        network::Request GetRequest() { return request_; }
        std::vector<entities::Message> GetData() {return messages_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_UPDATE_CHAT_CONVERTER_H
