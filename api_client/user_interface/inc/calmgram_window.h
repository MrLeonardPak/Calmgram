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

#include <QMutex>

#include <memory>
#include <string>

#include "interfaces_user_uc.h"
#include "signal_sender.h"

namespace calmgram::api_client::user_interface {

class CalmgramWindow : public QMainWindow {
  Q_OBJECT

 public:
  CalmgramWindow(std::shared_ptr<use_case::IUserUC> user_uc);
  ~CalmgramWindow() override;
 public slots:
  void RefreshSlot();
 signals:
  void StatusOn();
  void StatusOff();
  void StopRefresh();
 private slots:
  void LoginClick();
  void ChatsItemClick(QListWidgetItem* item);
  void LogoutClick();
  void MsgItemClick(QListWidgetItem* item);
  void MsgActionClick();
  void AddChatClick();
  void MsgSendClick();

 private:
  QWidget* uiWidget;

  QLineEdit* user_login_;  // поле для ввода логина
  QLineEdit* password_;    // поле для пароля
  QPushButton* login_;     // кнопка авторизации

  QVBoxLayout* init_layout_;

  QLabel* user_name_;      // поле с ID пользователя
  QListWidget* chats_;     // поле с чатами
  QLineEdit* second_id_;   // поле ID при добавлении чата
  QPushButton* add_chat_;  // кнопка добавления чата

  QLabel* chat_id_;      // поле с ID открытого чата
  QPushButton* logout_;  // кнопка выхода
  QListWidget* chat_;    // поле с нынешним чатом
  QLineEdit* message_;   // поле для ввода сообщения
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

  QMutex mutex;
  SignalSender t;
};

}  // namespace calmgram::api_client::user_interface

#endif  // API_CLIENT_CALMGRAM_WNDOW_H
