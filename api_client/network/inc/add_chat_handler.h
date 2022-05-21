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

        bool Execute(std::vector<int> ids) override;

        bool DataToRequest(std::vector<int> ids);
        bool ResponseToData(std::string response);

        int GetData() override { return output_; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_ADD_CHAT_HANDLER_H
