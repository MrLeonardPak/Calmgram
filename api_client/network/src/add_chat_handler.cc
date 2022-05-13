#include "add_chat_handler.h"

namespace calmgram::api_client::network {

    bool AddChatHandler::Execute(int id_1, int id_2) {
        if (id_1 == id_2)
            return true;
        return false;
    }

}
