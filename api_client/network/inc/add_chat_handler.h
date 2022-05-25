#ifndef API_CLIENT_ADD_CHAT_HANDLER_H
#define API_CLIENT_ADD_CHAT_HANDLER_H

#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class AddChatHandler : public IAddChat {
    private:
        std::string request_;
        int output_;
        
    public:
        AddChatHandler() = default;
        ~AddChatHandler() = default;

        bool Execute(std::vector<std::string> const& target_logins, std::string const& token) override;

        bool DataToRequest(std::vector<std::string> const& target_logins, std::string const& token);
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_ADD_CHAT_HANDLER_H
