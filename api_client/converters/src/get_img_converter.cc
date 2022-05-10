#include "get_img_converter.h"

namespace calmgram::api_client::converters {

    bool GetImageConverter::DataToRequest(std::string server_url) {
        // ....
        if (server_url.empty()) {
            return true;
        }
        return false;
    }
    bool GetImageConverter::ResponseToData(std::string response) {
        // ....
        if ( response.empty()) {
         return true;
        }
        return false;
    }

} // namespace calmgram::api_client::converters