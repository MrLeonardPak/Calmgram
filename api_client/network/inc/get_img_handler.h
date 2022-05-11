#ifndef API_CLIENT_GET_IMAGE_HANDLER_H
#define API_CLIENT_GET_IMAGE_HANDLER_H

#include "get_img_converter.h"
#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class GetImageHandler {
    private:
        std::string server_url_;
        converters::GetImageConverter converter_;
        std::string output_;
    public:
        GetImageHandler(std::string server_url)
            : server_url_(std::move(server_url)) {}
        ~GetImageHandler() = default;

        bool Execute();
        std::string GetData() { return output_; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_GET_IMAGE_HANDLER_H
