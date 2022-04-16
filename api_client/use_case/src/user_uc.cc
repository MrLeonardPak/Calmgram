#include "user_uc.h"

namespace calmgram::api_client::use_case {

    UserUseCase::UserUseCase(int id) {
        // initialization
    }

    std::vector<int> UserUseCase::GetChats() {
        std::vector<int> tmp;
        //logic
        return tmp;
    }

    std::vector<entities::Message> UserUseCase::OpenChat(int chat_id) {
        std::vector<entities::Message> tmp;
        // logic
        return tmp;
    }

    bool UserUseCase::CreateChat(int target_id) {
        // logic
        return true;
    }

    bool UserUseCase::SendMessage(entities::Content content, int chat_id) {
        // logic
        return true;
    }

    std::vector<int> UserUseCase::UpdateChats() {
        std::vector<int> tmp;
        //logic
        return tmp;
    }

} // calmgram::api_client::use_case
