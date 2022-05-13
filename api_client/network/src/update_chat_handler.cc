#include "update_chat_handler.h"

namespace calmgram::api_client::network {

    bool UpdateChatHandler::Execute(int chat_id, time_t last_update) {
        if (chat_id >=0 && last_update >=100)
            return false;
        return true;
    }

}
