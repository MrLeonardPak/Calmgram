#ifndef API_CLIENT_ADD_CHAT_HANDLER_H
#define API_CLIENT_ADD_CHAT_HANDLER_H

#include "add_chat_converter.h"

namespace calmgram::api_client::network {

    class AddChatHandler {
    private:
        int id_1_;
        int id_2_;
        converters::AddChatConverter converter_;
        int output;
    public:
        AddChatHandler(int id_1,
                       int id_2)
          : id_1_(id_1),
            id_2_(id_2) {}
        ~AddChatHandler() = default;

        bool Execute();
        int GetData() { return output; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_ADD_CHAT_HANDLER_H
