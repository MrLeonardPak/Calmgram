#include "get_img_converter.h"

#include <iostream>

namespace calmgram::api_client::converters {

    bool GetImageConverter::DataToRequest(std::string server_url) {
 
        try {
            // ....
            if (server_url.empty()) {
                return false;
            }
            request_ = server_url;
        }catch (std::exception const& e) {
            std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
            return false;
        }
        
        return true;
    }
    bool GetImageConverter::ResponseToData(std::string response) {
        try {
            // ....
            if ( response.empty()) {
                return false;
            }
            client_url_ = response;
            
        } catch (std::exception const& e) {
            std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
            return false;
        }
        return true;
    }

} // namespace calmgram::api_client::converters