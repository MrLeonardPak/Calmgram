//#include "core.h"
#include <QApplication>


#include "add_chat_handler.h"
#include "auth_handler.h"
#include "send_msg_handler.h"
#include "update_chat_handler.h"
#include "report_handler.h"
#include "user_uc.h"
#include "calmgram_window.h"

int main (int argc, char *argv[]) {
    QApplication a(argc, argv);
//    calmgram::api_client::core::Core core;
//    core.run();

    auto update_chat_handler = std::make_shared<calmgram::api_client::network::UpdateChatHandler>();
    auto send_msg_handler = std::make_shared<calmgram::api_client::network::SendMessageHandler>();
    auto add_chat_handler = std::make_shared<calmgram::api_client::network::AddChatHandler>();
    auto auth_handler = std::make_shared<calmgram::api_client::network::AuthorisationHandler>();
    auto report_handler = std::make_shared<calmgram::api_client::network::ReportHandler>();

    auto user_uc = std::make_shared<calmgram::api_client::use_case::UserUseCase>(
        update_chat_handler, send_msg_handler, add_chat_handler, auth_handler, report_handler);
     calmgram::api_client::user_interface::CalmgramWindow w(user_uc);
     w.show();
    return a.exec();
}
