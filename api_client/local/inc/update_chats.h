#ifndef API_CLIENT_UPDATE_CHATS_H
#define API_CLIENT_UPDATE_CHATS_H

#include "interfaces_handlers.h"

namespace calmgram::api_client::local {
    
    class UpdateChatsHandler : public network::IUpdateChats {
    private: 
        std::vector<entities::EmptyChat> output_;
    public:
        UpdateChatsHandler() = default;
        ~UpdateChatsHandler() = default;

        bool Execute(std::string const& token) override {
            output_.clear();
            size_t chat_cnt = rand() % 5;
            for (size_t i = 0; i < chat_cnt; ++i) {
                entities::EmptyChat tmp_chat;
                tmp_chat.id = i;
                tmp_chat.companions.push_back("John");
                tmp_chat.companions.push_back("Mark");
                output_.push_back(tmp_chat);
            }
            return true;
        }

        std::vector<entities::EmptyChat> GetData() override { return output_; }
    };

} // namespace calmgram::api_client::local

#endif //API_CLIENT_UPDATE_CHATS_H
