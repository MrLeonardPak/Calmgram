#ifndef API_CLIENT_UPDATE_CHAT_HENDLER_H
#define API_CLIENT_UPDATE_CHAT_HENDLER_H

#include "interfaces_handlers.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::network {

    class UpdateChatHandler : public IUpdateChat {
    private:
        std::string request_;
        std::vector<entities::Message> output_;
    public:
        UpdateChatHandler() = default;
        ~UpdateChatHandler() = default;

        bool Execute(int chat_id, time_t last_update, std::string const& token) override;
        
        bool DataToRequest(int chat_id, time_t last_update, std::string const& token);
        bool ResponseToData(std::string response);
        
        std::vector<entities::Message> GetData() override { return output_; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_UPDATE_CHAT_HENDLER_H
