#ifndef API_CLIENT_SEND_MSG_HENDLER_H
#define API_CLIENT_SEND_MSG_HENDLER_H

#include "send_msg_converter.h"
#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class SendMessageHandler : public ISendMessage{
    private:
        converters::SendMessageConverter converter_;
        bool output;
    public:
        SendMessageHandler() = default;
        ~SendMessageHandler() = default;

        bool Execute(int chat_id, int user_id, entities::Content content) override;
        bool GetData() override { return output; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_SEND_MSG_HENDLER_H
