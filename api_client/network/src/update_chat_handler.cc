#include "update_chat_handler.h"

namespace calmgram::api_client::network {

    bool UpdateChatHandler::Execute(int user_id, int chat_id, time_t last_update) {
        converter_.DataToRequest(user_id, chat_id, last_update);
        std::string request = converter_.GetRequest();
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request, "chat/update", true);
        converter_.ResponseToData(response);
        output = converter_.GetData();
        return true;
    }

}
