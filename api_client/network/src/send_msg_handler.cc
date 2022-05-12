#include "send_msg_handler.h"

namespace calmgram::api_client::network {

    bool SendMessageHandler::Execute(int chat_id, int user_id, entities::Content content) {
        if (!converter_.DataToRequest(chat_id,user_id,content)) {
            return false;
        }
        std::string request = converter_.GetRequest();
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request, "/chat/send", false);
        if (response == "Error") {
            return false;
        }
        if (!converter_.ResponseToData(response)) {
            return false;
        }
        output_ = converter_.GetData();
        return true;
    }

}

