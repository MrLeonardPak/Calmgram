#include "request_sender.h"

namespace calmgram::api_client::network {

    Response RequestSender::Execute(Request request) {
        Response tmp;
        if(request.body.empty())
            return tmp;
        return tmp;
    }

} // namespace calmgram::api_client::network


