#ifndef API_CLIENT_UPDATE_CHATS_HANDLER_H
#define API_CLIENT_UPDATE_CHATS_HANDLER_H

#include "interfaces_handlers.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::network {
    
    class UpdateChatsHandler : public IUpdateChats {
    private: 
        std::string request_;
        std::vector<entities::EmptyChat> output_;
    public:
        UpdateChatsHandler() = default;
        ~UpdateChatsHandler() = default;

        bool Execute(std::string const& token) override;

        bool DataToRequest(std::string const& token);
        bool ResponseToData(std::string response);
        std::vector<entities::EmptyChat> GetData() override { return output_; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_UPDATE_CHATS_HANDLER_H
