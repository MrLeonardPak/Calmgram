#include "add_chat_handler.h"

namespace calmgram::api_client::network {

    bool AddChatHandler::Execute(int id_1, int id_2) {
        converter_.DataToRequest(id_1,id_2);
        std::string request = converter_.GetRequest();
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request);
        converter_.ResponseToData(response);
        output = converter_.GetData();
        return true;
    }

}
