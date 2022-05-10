#include "get_img_handler.h"

namespace calmgram::api_client::network {

    bool GetImageHandler::Execute() {
        converter_.DataToRequest(server_url_);
        std::string request = converter_.GetRequest();
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request, "/chat/img", false);
        converter_.ResponseToData(response);
        output = converter_.GetData();
        return true;
    }

}
