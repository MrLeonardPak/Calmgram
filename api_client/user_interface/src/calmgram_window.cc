#include <QAction>
#include <QMenu>
#include <QMessageBox>

#include "calmgram_window.h"

namespace calmgram::api_client::user_interface {

CalmgramWindow::CalmgramWindow(std::shared_ptr<use_case::IUserUC> user_uc)
    : user_(user_uc) {
  uiWidget = new QWidget(this);
  setCentralWidget(uiWidget);

  LoginWindow();
}

CalmgramWindow::~CalmgramWindow() {
  qDeleteAll(uiWidget->children());
}

void CalmgramWindow::LoginWindow() {
  qDeleteAll(uiWidget->children());
  user_login_ = new QLineEdit(uiWidget);
  user_login_->setPlaceholderText("Enter login...");
  password_ = new QLineEdit(uiWidget);
  password_->setPlaceholderText("Enter password...");
  password_->setEchoMode(QLineEdit::Password);
  login_ = new QPushButton("Login", uiWidget);
  connect(login_, SIGNAL(clicked()), this, SLOT(LoginClick()));

  init_layout_ = new QVBoxLayout();
  init_layout_->addWidget(user_login_);
  init_layout_->addWidget(password_);
  init_layout_->addWidget(login_);
  uiWidget->setLayout(init_layout_);
}

void CalmgramWindow::MainWindow(std::string login) {
  qDeleteAll(uiWidget->children());
  // слой с ID чата, кнопкой обновления и со списком чатов
  user_name_ = new QLabel("User: " + QString::fromStdString(login));
  user_name_->setWhatsThis(QString::fromStdString(login));
  chats_ = new QListWidget(uiWidget);
  std::vector<entities::EmptyChat> chats = user_->GetChats();
  for (size_t i = 0; i < chats.size(); i++) {
    QListWidgetItem* item = new QListWidgetItem;
    item->setText("chat with ");
    for (std::string companion : chats[i].companions) {
      item->setText(item->text() + QString::fromStdString(companion) + " ");
    }
    item->setWhatsThis(QString::number(chats[i].id));
    chats_->addItem(item);
  }
  connect(chats_, SIGNAL(itemClicked(QListWidgetItem*)), this,
          SLOT(ChatsItemClick(QListWidgetItem*)));
  
  refresh_ = new QPushButton("Refresh", uiWidget);
  connect(refresh_, SIGNAL(clicked()), this, SLOT(RefreshClick()));

  chats_layout_ = new QVBoxLayout();
  chats_layout_->addWidget(user_name_);
  chats_layout_->addWidget(chats_);
  chats_layout_->addWidget(refresh_);

  // слой с добавлением нового чата
  second_id_ = new QLineEdit(uiWidget);
  second_id_->setPlaceholderText("Friend login...");
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
  layout_->setColumnMinimumWidth(0, 200);
  layout_->setColumnMinimumWidth(1, 400);

  layout_->setRowStretch(0, 1);
  layout_->setRowStretch(1, 0);
  layout_->setRowMinimumHeight(0, 300);
  layout_->setRowMinimumHeight(1, 50);

  uiWidget->setLayout(layout_);
  
  RefreshThread();
}



void CalmgramWindow::RefreshThread() {
  // pthread_t thr;
  // void* ptr = new std::shared_ptr<use_case::IUserUC>(user_);
  // if(pthread_create(&thr, nullptr, RefreshRoutine, (void*) ptr) != 0)
  //   QMessageBox::warning(uiWidget, "Error", "pthread_create failed");
}

void *CalmgramWindow::RefreshRoutine(void* arg) {

}

void CalmgramWindow::Refresh(std::vector<entities::EmptyChat> updated_chats) {
  chats_->clear();
  std::vector<entities::EmptyChat> chats = user_->GetChats();
  bool delete_opened = true;
  for (auto chat : chats) {
    if (chat.id == chat_id_->whatsThis().toInt()) {
      delete_opened = false;
    }
    auto idx = std::find_if(updated_chats.begin(), updated_chats.end(), [=](entities::EmptyChat const& upd_chat){ return chat.id == upd_chat.id; });
    QListWidgetItem* item = new QListWidgetItem;
    if (idx == updated_chats.end()) {
      // item->setText("chat " + QString::number(chat.id));
      item->setText("chat with ");
      for (std::string companion : chat.companions) {
        item->setText(item->text() + QString::fromStdString(companion) + " ");
      }
    } else {
      if (chat.id != chat_id_->whatsThis().toInt()) {
        // item->setText("chat " + QString::number(chat.id) + "(*)");
        item->setText("chat with ");
        for (std::string companion : chat.companions) {
          item->setText(item->text() + QString::fromStdString(companion) + " ");
        }
        item->setText(item->text() + "(*)");
      } else {
        OpenChat();
        // item->setText("chat " + QString::number(chat.id));
        item->setText("chat with ");
        for (std::string companion : chat.companions) {
          item->setText(item->text() + QString::fromStdString(companion) + " ");
        }
      }
    }
    item->setWhatsThis(QString::number(chat.id));
    chats_->addItem(item);
  }
  if (delete_opened) {
    chat_id_->setText("Chat: ");
    chat_id_->setWhatsThis("-1");
    chat_->clear();
  }
}

void CalmgramWindow::OpenChat() {
  chat_->clear();
  chat_id_->setText("Chat: " + chat_id_->whatsThis());
  std::vector<entities::Message> msgs =
      user_->OpenChat(chat_id_->whatsThis().toInt());
  for (auto msg : msgs) {
    QListWidgetItem* item = new QListWidgetItem;
    if (msg.is_marked) {
      item->setText("user " + QString::fromStdString(msg.sender) + ":*censored*");
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
  std::string login = user_login_->text().toStdString();
  try {
    user_->Auth(login, password_->text().toStdString());
  } catch (std::exception const& e) {
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
  MainWindow(login);
}

void CalmgramWindow::RefreshClick() {
  try {
    Refresh(user_->UpdateChats());
  } catch (const std::exception& e) {
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
}

void CalmgramWindow::ChatsItemClick(QListWidgetItem* item) {
  item->setText(item->text().remove("(*)"));
  chat_id_->setWhatsThis(item->whatsThis());
  OpenChat();
}

void CalmgramWindow::MsgItemClick(QListWidgetItem* item) {
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
}

void CalmgramWindow::MsgActionClick() {
  QListWidgetItem* item = chat_->selectedItems().first();
  if(item->toolTip().isEmpty()) {
      user_->ReportAboutMark(item->whatsThis().toStdString(), true);
  } else {
      user_->ReportAboutMark(item->whatsThis().toStdString(), false);
  }
}

void CalmgramWindow::AddChatClick() {
  QListWidgetItem* item = new QListWidgetItem;
  try {
    user_->CreateChat(std::vector<std::string>{second_id_->text().toStdString()});
  } catch (const std::exception& e) {
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
}

void CalmgramWindow::MsgSendClick() {
  if (chat_id_->whatsThis() == "-1") {
    return;
  }
  try {
    user_->SendMessage(message_->text().toStdString(),
                       chat_id_->whatsThis().toInt());
    message_->clear();
  } catch (const std::exception& e) {
    QMessageBox::warning(uiWidget, "Error", e.what());
    return;
  }
}
}  // namespace calmgram::api_client::user_interface
