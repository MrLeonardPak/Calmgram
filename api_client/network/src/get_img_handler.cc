#include "get_img_handler.h"

namespace calmgram::api_client::network {

    bool GetImageHandler::Execute() {
        if (!converter_.DataToRequest(server_url_)) {
            return false;
        }
        std::string request = converter_.GetRequest();
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request, "/chat/img", false);
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
