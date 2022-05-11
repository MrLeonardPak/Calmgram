#include "auth_handler.h"

namespace calmgram::api_client::network {

    bool AuthorisationHandler::Execute(int id) {
        converter_.DataToRequest(id);
        std::string request = converter_.GetRequest();
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request, "/auth", false);
        converter_.ResponseToData(response);
        output = converter_.GetData();
        return true;
    }

}
