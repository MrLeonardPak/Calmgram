#ifndef API_CLIENT_CALMGRAM_WNDOW_H
#define API_CLIENT_CALMGRAM_WNDOW_H

#include <QMainWindow>

#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QErrorMessage>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <string>

#include "interfaces_user_uc.h"

namespace calmgram::api_client::user_interface {


    class CalmgramWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        CalmgramWindow(std::shared_ptr<use_case::IUserUC> user_uc);
        ~CalmgramWindow() override;

    private slots:
        void LoginClick();
        void RefreshClick();
        void ChatsItemClick(QListWidgetItem* item);
        void MsgItemClick(QListWidgetItem* item);
        void MsgActionClick();
        void AddChatClick();
        void MsgSendClick();

    private:
        QWidget* uiWidget;

        QLineEdit* user_id_; // поле для ввода ID
        QPushButton* login_; // кнопка авторизации

        QVBoxLayout * init_layout_;

        QLabel* user_name_; // поле с ID пользователя
        QListWidget* chats_; // поле с чатами
        QPushButton* refresh_; // обновление
        QLineEdit* second_id_; // поле ID при добавлении чата
        QPushButton* add_chat_; // кнопка добавления чата

        QLabel* chat_id_; // поле с ID открытого чата
        QListWidget* chat_; // поле с нынешним чатом
        QLineEdit* message_; // поле для ввода сообщения
        QPushButton* send_msg_; // кнопка для отправки сообщения

        QVBoxLayout* chats_layout_;
        QVBoxLayout* add_chat_layout_;
        QVBoxLayout* chat_layout_;
        QHBoxLayout* send_msg_layout_;
        QGridLayout* layout_;

        std::shared_ptr<use_case::IUserUC> user_;

        void LoginWindow();
        void MainWindow(int id);
        void Refresh(std::vector<int> const& updated_chats);
        void OpenChat();

    };


} // calmgram::api_client::user_interface

#endif //API_CLIENT_CALMGRAM_WNDOW_H
