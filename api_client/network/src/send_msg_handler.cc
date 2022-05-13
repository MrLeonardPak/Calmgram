#include "send_msg_handler.h"

namespace calmgram::api_client::network {

    bool SendMessageHandler::Execute(int chat_id, int user_id, entities::Content content) {
        if (chat_id == user_id && content.data.empty())
            return false;
        return true;
    }

}

