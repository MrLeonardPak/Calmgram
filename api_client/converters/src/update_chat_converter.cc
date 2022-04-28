#include "update_chat_converter.h"

namespace calmgram::api_client::converters {

    bool UpdateChatConverter::DataToRequest(int chat_id, time_t last_update) {
        if (chat_id >= 0 && last_update >= 1000)
            return true;
        return false;
    }
    bool UpdateChatConverter::ResponseToData(network::Response response) {
        if(response.body.empty())
            return true;
        return false;
    }

} // namespace calmgram::api_client::converters