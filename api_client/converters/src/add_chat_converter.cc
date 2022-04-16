#include "add_chat_converter.h"

namespace calmgram::api_client::converters {

    bool AddChatConverter::DataToRequest(int id_1, int id_2) {
        // logic
        return true;
    }

    bool AddChatConverter::ResponseToData(network::Response response) {
        // logic
        return true;
    }

} // namespace calmgram::api_client::converters