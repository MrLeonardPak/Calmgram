#include <QAction>
#include <QMenu>
#include <QMessageBox>

#include <sstream>

#include "calmgram_window.h"

namespace calmgram::api_client::user_interface {

CalmgramWindow::CalmgramWindow(std::shared_ptr<use_case::IUserUC> user_uc)
    : user_(user_uc) {
  uiWidget = new QWidget(this);
  setCentralWidget(uiWidget);

  this->setStyleSheet(
      "QWidget#uiWidget {"
      "background-color: qlineargradient( x1: 0, y1: 0, x2: "
      "0, y2: 1, stop : 0 #5C95FF, stop : 1 #70D6FF);"
      "}"
      "QLineEdit { "
      " border: 2px solid #8f8f91;"
      " border-radius: 4px;"
      " background: #F0F0D1; selection-background-color: #FAFAEF; "
      " height: 40;"
      "}"
      "QLabel {"
      "font: bold 14px;"
      "}"
      "QListWidget { "
      " border: 2px solid #8f8f91;"
      " border-radius: 2px;"
      " background-color: qlineargradient( x1: 1, y1: 1, x2: "
      "0, y2: 0, stop : 0 #F2F3D9, stop : 1 #F0F0D1);"
      "}"
      "QPushButton {"
      " border: 2px solid #8f8f91;"
      " border-radius: 6px;"
      " color: #041C2C;"
      " background-color: #DBAFC1;"
      "width: 80px;"
      "height: 40px;"
      "}"
      "QPushButton#logout {"
      "max-width: 60px;"
      "max-height: 25px;"
      "}"
      "QPushButton:pressed {"
      " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
      " stop: 0 #CC998D, stop: 1 #a85d4c);"
      "}"
      "QPushButton:flat {"
      " border: none;"
      "}"
      "QPushButton:default {"
      " border-color: navy;"
      "}"
      "QMessageBox {"
      "background-color: qlineargradient( x1: 0, y1: 0, x2: "
      "0, y2: 1, stop : 0 #5C95FF, stop : 1 #70D6FF);"
      "}");
  uiWidget->setObjectName("uiWidget");
  QObject::connect(&t, SIGNAL(Ping()), this, SLOT(RefreshSlot()));
  QObject::connect(this, SIGNAL(StatusOn()), &t, SLOT(StatusOn()));
  QObject::connect(this, SIGNAL(StatusOff()), &t, SLOT(StatusOff()));
  QObject::connect(this, SIGNAL(StopRefresh()), &t, SLOT(StopRefresh()));
  t.start();
  LoginWindow();
}

CalmgramWindow::~CalmgramWindow() {
  emit StopRefresh();
  user_->Logout();
  DeleteLayout(uiWidget->layout());
  t.quit();
  t.wait();
}

void CalmgramWindow::LoginWindow() {
  emit StatusOff();
  DeleteLayout(uiWidget->layout());
  user_login_ = new QLineEdit(uiWidget);
  user_login_->setPlaceholderText("Enter login...");
  QRegExp rx("^[a-zA-Z0-9]{0,10}$");
  user_login_->setValidator(new QRegExpValidator(rx, this));
  password_ = new QLineEdit(uiWidget);
  password_->setPlaceholderText("Enter password...");
  password_->setEchoMode(QLineEdit::Password);
  login_ = new QPushButton("Login", uiWidget);
  login_->setShortcut(Qt::Key_Return);
  connect(login_, SIGNAL(clicked()), this, SLOT(LoginClick()));

  init_layout_ = new QVBoxLayout();
  init_layout_->addWidget(user_login_);
  init_layout_->addWidget(password_);
  init_layout_->addWidget(login_);
  uiWidget->setLayout(init_layout_);
}

void CalmgramWindow::MainWindow(std::string login) {
  DeleteLayout(uiWidget->layout());
  // слой с ID чата, кнопкой обновления и со списком чатов
  user_name_ = new QLabel("User: " + QString::fromStdString(login));
  user_name_->setWhatsThis(QString::fromStdString(login));
  logout_ = new QPushButton("Logout", uiWidget);
  logout_->setObjectName("logout");
  connect(logout_, SIGNAL(clicked()), this, SLOT(LogoutClick()));
  chats_ = new QListWidget(uiWidget);
  connect(chats_, SIGNAL(itemClicked(QListWidgetItem*)), this,
          SLOT(ChatsItemClick(QListWidgetItem*)));

  user_layout_ = new QHBoxLayout();
  user_layout_->addWidget(user_name_);
  user_layout_->addWidget(logout_);
  chats_layout_ = new QVBoxLayout();
  chats_layout_->addLayout(user_layout_);
  chats_layout_->addWidget(chats_);

  // слой с добавлением нового чата
  second_id_ = new QLineEdit(uiWidget);
  second_id_->setPlaceholderText("Friend's logins separated by space...");
  QRegExp rx2("^[a-zA-Z0-9 ]{0,100}$");
  second_id_->setValidator(new QRegExpValidator(rx2, this));
  add_chat_ = new QPushButton("Add chat", uiWidget);
  connect(add_chat_, SIGNAL(clicked()), this, SLOT(AddChatClick()));
  add_chat_layout_ = new QVBoxLayout();
  add_chat_layout_->addWidget(second_id_);
  add_chat_layout_->addWidget(add_chat_);

  //слой с ID чата и самим чатом
  chat_id_ = new QLabel("Chat: ");
  chat_id_->setWhatsThis("-1");
  chat_ = new QListWidget(uiWidget);
  connect(chat_, SIGNAL(itemClicked(QListWidgetItem*)), this,
          SLOT(MsgItemClick(QListWidgetItem*)));
  chat_layout_ = new QVBoxLayout();
  chat_layout_->addWidget(chat_id_);
  chat_layout_->addWidget(chat_);

  //слой отправки сообщения
  message_ = new QLineEdit(uiWidget);
  message_->setPlaceholderText("Msg...");
  send_msg_ = new QPushButton("Send", uiWidget);
  connect(send_msg_, SIGNAL(clicked()), this, SLOT(MsgSendClick()));

  send_msg_layout_ = new QHBoxLayout();
  send_msg_layout_->addWidget(message_);
  send_msg_layout_->addWidget(send_msg_);

  // финальное обьединение слоев
  layout_ = new QGridLayout();

  layout_->addLayout(chats_layout_, 0, 0);
  layout_->addLayout(add_chat_layout_, 1, 0);
  layout_->addLayout(chat_layout_, 0, 1);
  layout_->addLayout(send_msg_layout_, 1, 1);

  layout_->setColumnStretch(0, 1);
  layout_->setColumnStretch(1, 4);
  layout_->setColumnMinimumWidth(0, 300);
  layout_->setColumnMinimumWidth(1, 500);

  layout_->setRowStretch(0, 1);
  layout_->setRowStretch(1, 0);
  layout_->setRowMinimumHeight(0, 400);
  layout_->setRowMinimumHeight(1, 100);

  uiWidget->setLayout(layout_);
  emit StatusOn();
}

void CalmgramWindow::Refresh() {
  chats_->clear();
  std::vector<entities::EmptyChat> chats = user_->GetChats();
  bool delete_opened = true;
  for (auto chat : chats) {
    QListWidgetItem* item = new QListWidgetItem;
    if (chat.id == chat_id_->whatsThis().toInt()) {
      delete_opened = false;
    }
    item->setText("Chat with ");
    if (!chat.companions.empty()) {
      for (std::string companion : chat.companions) {
        item->setText(item->text() + QString::fromStdString(companion) + " ");
      }
    } else {
      item->setText(item->text() + "yourself ");
    }
    if (chat.is_updated && chat.id != chat_id_->whatsThis().toInt()) {
      item->setText(item->text() + "(*)");
    }
    item->setWhatsThis(QString::number(chat.id));
    chats_->addItem(item);
  }
  if (delete_opened) {
    chat_id_->setText("Chat: ");
    chat_id_->setWhatsThis("-1");
    chat_->clear();
  } else {
    OpenChat();
  }
}

void CalmgramWindow::OpenChat() {
  chat_->clear();
  std::vector<entities::Message> msgs =
      user_->OpenChat(chat_id_->whatsThis().toInt());
  for (auto msg : msgs) {
    QListWidgetItem* item = new QListWidgetItem;
    if (msg.is_marked) {
      item->setText("user " + QString::fromStdString(msg.sender) +
                    ":*censored*");
      item->setToolTip(QString::fromStdString(msg.content.data));
    } else {
      item->setText("user " + QString::fromStdString(msg.sender) + ": " +
                    QString::fromStdString(msg.content.data));
    }
    item->setWhatsThis(QString::fromStdString(msg.content.data));
    chat_->addItem(item);
  }
}

void CalmgramWindow::LoginClick() {
  if (user_login_->text().isEmpty()) {
    QMessageBox::warning(uiWidget, "Error", "Please enter login");
    return;
  }
  if (password_->text().isEmpty()) {
    QMessageBox::warning(uiWidget, "Error", "Please enter password");
    return;
  }
  std::string login = user_login_->text().toStdString();
  try {
    user_->Auth(login, password_->text().toStdString());
  } catch (std::exception const& e) {
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
  MainWindow(login);
}

void CalmgramWindow::RefreshSlot() {
  if (mutex.tryLock(500)) {
    try {
      user_->UpdateChats();
      Refresh();
      mutex.unlock();
    } catch (const std::exception& e) {
      user_->Logout();
      LoginWindow();
      mutex.unlock();
      QMessageBox::warning(uiWidget, "Error",
                           "Failed to connect to the server");
    }
  }
}

void CalmgramWindow::ChatsItemClick(QListWidgetItem* item) {
  mutex.lock();
  try {
    item->setText(item->text().remove("(*)"));
    chat_id_->setText(item->text());
    chat_id_->setWhatsThis(item->whatsThis());
    OpenChat();
    mutex.unlock();
  } catch (const std::exception& e) {
    mutex.unlock();
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
}

void CalmgramWindow::LogoutClick() {
  mutex.lock();
  user_->Logout();
  LoginWindow();
  mutex.unlock();
}

void CalmgramWindow::MsgItemClick(QListWidgetItem* item) {
  mutex.lock();
  try {
    QMenu* menu = new QMenu(this);
    QAction* action;
    if (item->toolTip().isEmpty()) {
      action = new QAction("It must be censored", this);
    } else {
      action = new QAction("It must be not censored", this);
    }
    QAction* close = new QAction("Close", this);
    connect(action, SIGNAL(triggered()), this, SLOT(MsgActionClick()));
    menu->addAction(action);
    menu->exec(QCursor::pos());
    mutex.unlock();
  } catch (const std::exception& e) {
    mutex.unlock();
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
}

void CalmgramWindow::MsgActionClick() {
  QListWidgetItem* item = chat_->selectedItems().first();
  try {
    if (item->toolTip().isEmpty()) {
      user_->ReportAboutMark(item->whatsThis().toStdString(), true);
    } else {
      user_->ReportAboutMark(item->whatsThis().toStdString(), false);
    }
  } catch (const std::exception& e) {
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
}

void CalmgramWindow::AddChatClick() {
  if (second_id_->text().isEmpty()) {
    QMessageBox::warning(uiWidget, "Error", "Enter friend's login");
    return;
  }
  std::string logins = second_id_->text().toStdString();
  std::stringstream ss(logins);
  std::vector<std::string> logins_vec;
  std::string login;
  while (ss >> login) {
    if (std::find(logins_vec.begin(), logins_vec.end(), login) ==
            logins_vec.end() &&
        !login.empty())
      logins_vec.push_back(login);
  }
  mutex.lock();
  try {
    user_->CreateChat(logins_vec);
    second_id_->clear();
    mutex.unlock();
  } catch (const std::exception& e) {
    mutex.unlock();
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
}

void CalmgramWindow::MsgSendClick() {
  if (message_->text().isEmpty()) {
    QMessageBox::warning(uiWidget, "Error", "Attempt to send empty message");
    return;
  }
  if (chat_id_->whatsThis() == "-1") {
    QMessageBox::warning(uiWidget, "Error", "First open chat");
    return;
  }
  mutex.lock();
  try {
    user_->SendMessage(message_->text().toStdString(),
                       chat_id_->whatsThis().toInt());
    message_->clear();
    mutex.unlock();
  } catch (const std::exception& e) {
    mutex.unlock();
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
}

void CalmgramWindow::DeleteLayout(QLayout* layout) {
  if (layout == nullptr) {
    return;
  }
  QLayoutItem* item;
  QLayout* sublayout;
  QWidget* widget;
  while ((item = layout->takeAt(0))) {
    if ((sublayout = item->layout()) != 0) {
      DeleteLayout(sublayout);
    } else if ((widget = item->widget()) != 0) {
      widget->hide();
      delete widget;
    } else {
      delete item;
    }
  }
  delete layout;
}
}  // namespace calmgram::api_client::user_interface
