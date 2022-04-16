#ifndef API_CLIENT_INTERFACES_USER_UC_H
#define API_CLIENT_INTERFACES_USER_UC_H

#include "entities.h"

#include <vector>

namespace calmgram::api_client::use_case {

    class IUserUC {
    public:
        ~IUserUC() = default;

        virtual std::vector<int> GetChats() = 0;
        virtual std::vector<entities::Message> OpenChat(int chat_id) = 0;
        virtual bool CreateChat(int target_id) = 0;
        virtual bool SendMessage(entities::Content content, int chat_id) = 0;
        virtual std::vector<int> UpdateChats() = 0;
    };
}  // namespace calmgram::api_server::use_case

#endif //API_CLIENT_INTERFACES_USER_UC_H
