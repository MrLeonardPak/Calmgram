#ifndef API_CLIENT_SEND_MSG_HENDLER_H
#define API_CLIENT_SEND_MSG_HENDLER_H

#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class SendMessageHandler : public ISendMessage{
    private:
        std::string request_;
        
    public:
        SendMessageHandler() = default;
        ~SendMessageHandler() = default;

        bool DataToRequest(int chat_id, entities::Content content, std::string const& token);
        
        bool Execute(int chat_id, entities::Content content, std::string const& token) override;
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_SEND_MSG_HENDLER_H
