#ifndef API_CLIENT_UPDATE_CHAT_HENDLER_H
#define API_CLIENT_UPDATE_CHAT_HENDLER_H

#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class UpdateChatHandler : public IUpdateChat {
    private:
        std::string request_;
        std::vector<entities::Message> output_;
    public:
        UpdateChatHandler() = default;
        ~UpdateChatHandler() = default;

        bool Execute(int user_id, int chat_id, time_t last_update) override;
        
        bool DataToRequest(int user_id, int chat_id, time_t last_update);
        bool ResponseToData(std::string response);
        
        std::vector<entities::Message> GetData() override { return output_; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_UPDATE_CHAT_HENDLER_H
