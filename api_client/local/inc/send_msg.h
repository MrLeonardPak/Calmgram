#ifndef API_CLIENT_SEND_MSG_H
#define API_CLIENT_SEND_MSG_H

#include "interfaces_handlers.h"

#include <iostream>

namespace calmgram::api_client::local {

    class SendMessageHandler : public network::ISendMessage{        
    public:
        SendMessageHandler() = default;
        ~SendMessageHandler() = default;
        
        bool Execute(int chat_id, entities::Content content, std::string const& token) override {
            std::cout << "msg: " << content.data << " sended in chat " << chat_id << std::endl;
            return true;
        }
    };

} // namespace calmgram::api_client::local

#endif //API_CLIENT_SEND_MSG_H
