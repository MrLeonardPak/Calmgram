#include "auth_converter.h"

namespace calmgram::api_client::converters {

    bool AuthorisationConverter::DataToRequest(int id) {
        // logic
        return true;
    }
    bool AuthorisationConverter::ResponseToData(network::Response response) {
        // logic
        return true;
    }

} // namespace calmgram::api_client::converters

