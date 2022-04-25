#ifndef API_CLIENT_ADD_CHAT_HANDLER_H
#define API_CLIENT_ADD_CHAT_HANDLER_H

#include "add_chat_converter.h"
#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class AddChatHandler : public IAddChat {
    private:
        int id_1_;
        int id_2_;
        converters::AddChatConverter converter_;
        int output;
    public:
        AddChatHandler() = default;
        ~AddChatHandler() = default;

        bool Execute(int id_1, int id_2) override;
        int GetData() override { return output; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_ADD_CHAT_HANDLER_H
