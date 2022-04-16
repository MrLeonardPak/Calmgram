#include "get_img_converter.h"

namespace calmgram::api_client::converters {

    bool GetImageConverter::DataToRequest(std::string server_url) {
        // logic
        return true;
    }
    bool GetImageConverter::ResponseToData(network::Response response) {
        // logic
        return true;
    }

} // namespace calmgram::api_client::converters