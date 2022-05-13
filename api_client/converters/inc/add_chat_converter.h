#ifndef API_CLIENT_ADD_CHAT_CONVERTER_H
#define API_CLIENT_ADD_CHAT_CONVERTER_H

#include "structs.h"

namespace calmgram::api_client::converters {

    class AddChatConverter {
    private:
        network::Request request_;
        int chat_id_{};
    public:
        AddChatConverter() = default;
        ~AddChatConverter() = default;

        bool DataToRequest(int id_1, int id_2);
        bool ResponseToData(network::Response response);
        network::Request GetRequest() { return request_; }
        int GetData() { return chat_id_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_ADD_CHAT_CONVERTER_H
