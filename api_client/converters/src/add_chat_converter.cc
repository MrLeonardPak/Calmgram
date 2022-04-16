#include "add_chat_converter.h"

namespace calmgram::api_client::converters {

    bool AddChatConverter::DataToRequest(int id_1, int id_2) {
        // logic
        if (id_1 == id_2)
            return true;
        return false;
    }

    bool AddChatConverter::ResponseToData(network::Response response) {
        if(response.body.empty())
            return true;
        return false;
    }

} // namespace calmgram::api_client::converters