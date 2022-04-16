#ifndef API_CLIENT_UPDATE_CHAT_HENDLER_H
#define API_CLIENT_UPDATE_CHAT_HENDLER_H

#include "update_chat_converter.h"
#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class UpdateChatHandler : public IUpdateChat {
    private:
        int chat_id_;
        time_t last_update_;
        converters::UpdateChatConverter converter_;
        std::vector<entities::Message> output;
    public:
        UpdateChatHandler() = default;
        ~UpdateChatHandler() = default;

        bool Execute(int chat_id, time_t last_update) override;
        std::vector<entities::Message> GetData() override { return output; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_UPDATE_CHAT_HENDLER_H
