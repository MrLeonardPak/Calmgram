#include "auth_converter.h"

namespace calmgram::api_client::converters {

    bool AuthorisationConverter::DataToRequest(int id) {
        if (id >= 0)
            return true;
        return false;
    }
    bool AuthorisationConverter::ResponseToData(network::Response response) {
        if(response.body.empty())
            return true;
        return false;
    }

} // namespace calmgram::api_client::converters

