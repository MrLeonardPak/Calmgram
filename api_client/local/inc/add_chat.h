#ifndef API_CLIENT_ADD_CHAT_H
#define API_CLIENT_ADD_CHAT_H

#include "interfaces_handlers.h"

#include <iostream>

namespace calmgram::api_client::local {

    class AddChatHandler : public network::IAddChat {
    private:        
    public:
        AddChatHandler() = default;
        ~AddChatHandler() = default;

        bool Execute(std::vector<std::string> const& target_logins, std::string const& token) override {
            std::cout << "Chat with ";
            for (auto& login : target_logins) {
                std::cout << login << " ";
            }
            std::cout << std::endl;
            return true;
        }
    };

} // namespace calmgram::api_client::local

#endif //API_CLIENT_ADD_CHAT_H
