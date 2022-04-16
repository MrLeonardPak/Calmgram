#ifndef API_CLIENT_UPDATE_CHAT_HENDLER_H
#define API_CLIENT_UPDATE_CHAT_HENDLER_H

#include "add_chat_converter.h"
#include "entities.h"
#include "interfaces_handler.h"

#include <vector>
#include <ctime>

namespace calmgram::api_client::network {

    class UpdateChatHandler : public IHandler{
    private:
        int chat_id_;
        time_t last_update_;
        converters::AddChatConverter converter_;
        std::vector<entities::Message> output;
    public:
        UpdateChatHandler(int chat_id,
                          time_t last_update)
          : chat_id_(chat_id),
            last_update_(last_update) {}
        ~UpdateChatHandler() = default;

        bool Execute() override;
        std::vector<entities::Message> GetData() { return output; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_UPDATE_CHAT_HENDLER_H
