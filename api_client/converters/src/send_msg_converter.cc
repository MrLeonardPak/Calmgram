#include "send_msg_converter.h"

namespace calmgram::api_client::converters {

    bool SendMessageConverter::DataToRequest(int chat_id, int user_id, entities::Content content) {
        // logic
        return true;
    }
    bool SendMessageConverter::ResponseToData(network::Response response) {
        // logic
        return true;
    }

} // namespace calmgram::api_client::converters