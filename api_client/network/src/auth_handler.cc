#include "auth_handler.h"

namespace calmgram::api_client::network {

    bool AuthorisationHandler::Execute(int id) {
        if (!converter_.DataToRequest(id)) {
            return false;
        }
        std::string request = converter_.GetRequest();
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request, "/auth", false);
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
