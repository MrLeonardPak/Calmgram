#ifndef API_CLIENT_USER_UC_H
#define API_CLIENT_USER_UC_H

#include "interfaces_user_uc.h"
#include "interfaces_handlers.h"

namespace calmgram::api_client::use_case {

    class UserUseCase : public IUserUC {
    private:
        entities::Profile profile_;
        std::shared_ptr<network::IAuthorisation> auth_;
        std::shared_ptr<network::IUpdateChats> update_chats_;
        std::shared_ptr<network::IUpdateChat> update_chat_;
        std::shared_ptr<network::ISendMessage> send_msg_;
        std::shared_ptr<network::IAddChat> add_chat_;
        std::shared_ptr<network::IReportAboutMark> report_;
    public:
        UserUseCase(std::shared_ptr<network::IAuthorisation> auth,
                    std::shared_ptr<network::IUpdateChats> update_chats,
                    std::shared_ptr<network::IUpdateChat> update_chat,
                    std::shared_ptr<network::ISendMessage> send_msg,
                    std::shared_ptr<network::IAddChat> add_chat,
                    std::shared_ptr<network::IReportAboutMark> report)
                : auth_(auth),
                  update_chats_(update_chats),
                  update_chat_(update_chat),
                  send_msg_(send_msg),
                  add_chat_(add_chat),
                  report_(report) {}
        ~UserUseCase() = default;


        void Auth(std::string const& login, std::string const& password) override;
        std::vector<entities::EmptyChat> GetChats() const override;
        std::vector<entities::Message> OpenChat(int chat_id) const override;
        void CreateChat(std::vector<std::string>  const& target_logins) const override;
        void SendMessage(std::string const& str, int chat_id)  const override;
        void ReportAboutMark(std::string const& msg, bool is_marked) const override;
        std::vector<entities::EmptyChat> UpdateChats() override;
    };
}  // namespace calmgram::api_server::use_case

#endif  //API_CLIENT_USER_UC_H
