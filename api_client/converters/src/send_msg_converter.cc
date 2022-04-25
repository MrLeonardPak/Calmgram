#include "send_msg_converter.h"

namespace calmgram::api_client::converters {

    bool SendMessageConverter::DataToRequest(int chat_id, int user_id, entities::Content content) {
        if(chat_id == user_id && content.data.empty())
            return true;
        return false;
    }
    bool SendMessageConverter::ResponseToData(network::Response response) {
        if(response.body.empty())
            return true;
        return false;
    }

} // namespace calmgram::api_client::converters