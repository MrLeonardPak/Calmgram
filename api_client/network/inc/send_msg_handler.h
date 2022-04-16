#ifndef API_CLIENT_SEND_MSG_HENDLER_H
#define API_CLIENT_SEND_MSG_HENDLER_H

#include <utility>

#include "send_msg_converter.h"
#include "entities.h"
#include "add_chat_converter.h"

namespace calmgram::api_client::network {

    class SendMessageHandler {
    private:
        int chat_id_;
        int user_id_;
        entities::Content content_;
        converters::AddChatConverter converter_;
        bool output;
    public:
        SendMessageHandler(int chat_id,
                           int user_id,
                           entities::Content content)
          : chat_id_(chat_id),
            user_id_(user_id),
            content_(std::move(content)) {}
        ~SendMessageHandler() = default;

        bool Execute();
        bool GetData() { return output; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_SEND_MSG_HENDLER_H
