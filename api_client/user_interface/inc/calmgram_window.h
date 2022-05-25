#ifndef API_CLIENT_CALMGRAM_WNDOW_H
#define API_CLIENT_CALMGRAM_WNDOW_H

#include <QMainWindow>

#include <QErrorMessage>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <memory>
#include <string>

#include "interfaces_user_uc.h"

namespace calmgram::api_client::user_interface {

class CalmgramWindow : public QMainWindow {
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

  QLineEdit* user_login_;  // поле для ввода логина
  QLineEdit* password_; // поле для пароля
  QPushButton* login_;  // кнопка авторизации

  QVBoxLayout* init_layout_;

  QLabel* user_name_;      // поле с ID пользователя
  QListWidget* chats_;     // поле с чатами
  QPushButton* refresh_;   // обновление
  QLineEdit* second_id_;   // поле ID при добавлении чата
  QPushButton* add_chat_;  // кнопка добавления чата

  QLabel* chat_id_;     // поле с ID открытого чата
  QListWidget* chat_;   // поле с нынешним чатом
  QLineEdit* message_;  // поле для ввода сообщения
  QPushButton* send_msg_;  // кнопка для отправки сообщения

  QVBoxLayout* chats_layout_;
  QVBoxLayout* add_chat_layout_;
  QVBoxLayout* chat_layout_;
  QHBoxLayout* send_msg_layout_;
  QGridLayout* layout_;

  std::shared_ptr<use_case::IUserUC> user_;

  void LoginWindow();
  void MainWindow(std::string login);
  void Refresh(std::vector<entities::EmptyChat> updated_chats);
  void OpenChat();

  void RefreshThread();
  void *RefreshRoutine (void* arg);
  
};

}  // namespace calmgram::api_client::user_interface

#endif  // API_CLIENT_CALMGRAM_WNDOW_H
