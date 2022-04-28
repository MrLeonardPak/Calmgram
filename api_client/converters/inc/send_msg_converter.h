#ifndef API_CLIENT_SEND_MSG_CONVERTER_H
#define API_CLIENT_SEND_MSG_CONVERTER_H

#include "structs.h"
#include "entities.h"

namespace calmgram::api_client::converters {

    class SendMessageConverter {
    private:
        network::Request request_;
        bool is_completed_{};

    public:
        SendMessageConverter() = default;
        ~SendMessageConverter() = default;

        bool DataToRequest(int chat_id, int user_id, entities::Content content);
        bool ResponseToData(network::Response response);
        network::Request GetRequest() { return request_; }
        bool GetData() {return is_completed_; }
    };


} // namespace calmgram::api_client::converters

#endif //API_CLIENT_SEND_MSG_CONVERTER_H
