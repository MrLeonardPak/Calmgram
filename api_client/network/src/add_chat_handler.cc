#include "add_chat_handler.h"

namespace calmgram::api_client::network {

    bool AddChatHandler::Execute(int id_1, int id_2) {
        int ids[]={id_1, id_2};
        if (!converter_.DataToRequest(ids,2)) {
            return false;
        }
        std::string request = converter_.GetRequest();
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request, "/chat/add",false);
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
