#include "user_uc.h"

namespace calmgram::api_client::use_case {

    UserUseCase::UserUseCase(int id) {
        if (id >= 0)
            id++;
    }

    std::vector<int> UserUseCase::GetChats() {
        std::vector<int> tmp;
        //logic
        return tmp;
    }

    std::vector<entities::Message> UserUseCase::OpenChat(int chat_id) {
        std::vector<entities::Message> tmp;
        if (chat_id >= 0)
            return tmp;
        return tmp;
    }

    bool UserUseCase::CreateChat(int target_id) {
        if (target_id >= 0)
            return false;
        return true;
    }

    bool UserUseCase::SendMessage(entities::Content content, int chat_id) {
        if (content.data.empty() && chat_id >= 0)
            return false;
        return true;
    }

    std::vector<int> UserUseCase::UpdateChats() {
        std::vector<int> tmp;
        //logic
        return tmp;
    }

} // calmgram::api_client::use_case
