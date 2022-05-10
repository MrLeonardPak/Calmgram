#include "send_msg_handler.h"

namespace calmgram::api_client::network {

    bool SendMessageHandler::Execute(int chat_id, int user_id, entities::Content content) {
        converter_.DataToRequest(chat_id,user_id,content);
        std::string request = converter_.GetRequest();
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request, "/chat/send", false);
        converter_.ResponseToData(response);
        output = converter_.GetData();
        return true;
    }

}

