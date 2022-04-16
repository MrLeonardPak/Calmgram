#include "update_chat_converter.h"

namespace calmgram::api_client::converters {

    bool UpdateChatConverter::DataToRequest(int chat_id, time_t last_update) {
        // logic
        return true;
    }
    bool UpdateChatConverter::ResponseToData(network::Response response) {
        // logic
        return true;
    }

} // namespace calmgram::api_client::converters