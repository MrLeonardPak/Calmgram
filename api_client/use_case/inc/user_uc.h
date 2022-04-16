#ifndef API_CLIENT_USER_UC_H
#define API_CLIENT_USER_UC_H

#include "entities.h"
#include "interfaces_user_uc.h"
#include "interfaces_handler.h"

namespace calmgram::api_client::use_case {

    class UserUseCase : public IUserUC {
    private:
        entities::Profile profile_;
        network::IHandler* handler_;

    public:
        UserUseCase(int id);
        ~UserUseCase() = default;

        std::vector<int> GetChats() override;
        std::vector<entities::Message> OpenChat(int chat_id) override;
        bool CreateChat(int target_id) override;
        bool SendMessage(entities::Content content, int chat_id) override;
        std::vector<int> UpdateChats() override;
    };
}  // namespace calmgram::api_server::use_case

#endif  //API_CLIENT_USER_UC_H
