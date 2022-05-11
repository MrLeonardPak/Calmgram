//
// Created by Иван on 16.04.2022.
//

#ifndef API_CLIENT_CALMGRAM_WNDOW_H
#define API_CLIENT_CALMGRAM_WNDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QListView>
#include <QErrorMessage>
#include <string>
#include <QVBoxLayout>

#include "interfaces_user_uc.h"

namespace calmgram::api_client::user_interface {
    QT_BEGIN_NAMESPACE
    namespace Ui {
        class CalmgramWindow;
    }
    QT_END_NAMESPACE

    class CalmgramWindow : public QWidget {
        Q_OBJECT

    public:
        CalmgramWindow();
        ~CalmgramWindow();
        void LoginClick();
        void Update();
        void FillChats(std::vector<int> new_ids);
        void OpenChat(int chat_id);
        std::string PrintMessage(entities::Message msg);

private slots:
        void ChatClick();
        void ChatAddClick();
        void ImgClick();
        void MsgClick();
        void RefreshClick();
    private:
        Ui::CalmgramWindow *ui;
        QLineEdit* user_id_;
        QPushButton* login_;
        QLabel* user_name_;
        QListWidget* chats_;
        QLineEdit* second_id_;
        QPushButton* add_chat_btn_;
        QLabel* chat_id_;
        QListView* chat_;
        QLineEdit* message_;
        QPushButton* send_img_;
        QPushButton* send_msg_;
        QPushButton* refresh_;
        use_case::IUserUC* user_;

        QVBoxLayout * init_layout;


        int opened_chat_id;

    };
} // calmgram::api_client::user_interface

#endif //API_CLIENT_CALMGRAM_WNDOW_H
