#ifndef API_CLIENT_UPDATE_CHAT_H
#define API_CLIENT_UPDATE_CHAT_H

#include "interfaces_handlers.h"

namespace calmgram::api_client::local {

    class UpdateChatHandler : public network::IUpdateChat {
    private:
        std::vector<entities::Message> output_;
    public:
        UpdateChatHandler() = default;
        ~UpdateChatHandler() = default;

        bool Execute(int chat_id, time_t last_update, std::string const& token) override {
            output_.clear();
            size_t msg_cnt = rand() % 3;
            for (size_t i = 0; i < msg_cnt; ++i) {
                entities::Message tmp_msg;
                tmp_msg.sender = (i % 2) ? "Mark" : "John";
                tmp_msg.is_marked = (i % 2) ? true : false;
                entities::Content content_tmp("Some text " + std::to_string(i));
                tmp_msg.time = last_update + i * chat_id;
                tmp_msg.content.type = entities::TEXT;
                tmp_msg.content.data = "Some text " + std::to_string(i);
                output_.push_back(tmp_msg);
            }
            return true;
        }
        
        std::vector<entities::Message> GetData() override { return output_; }
    };

} // namespace calmgram::api_client::local

#endif //API_CLIENT_UPDATE_CHAT_H
