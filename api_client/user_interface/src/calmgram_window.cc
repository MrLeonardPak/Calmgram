#include <iostream>
#include <QMessageBox>
#include <QMenu>
#include <QAction>

#include "calmgram_window.h"

namespace calmgram::api_client::user_interface {
 
    CalmgramWindow::CalmgramWindow(std::shared_ptr<use_case::IUserUC> user_uc)
        : user_(user_uc)
    {

        uiWidget = new QWidget( this );
        setCentralWidget( uiWidget );

        LoginWindow();

    }

    CalmgramWindow::~CalmgramWindow()
    {
        qDeleteAll(uiWidget->children());
    }

    void CalmgramWindow::LoginWindow() {
        qDeleteAll(uiWidget->children());
        user_id_= new QLineEdit(uiWidget);
        user_id_->setPlaceholderText("Enter user ID...");
        login_ = new QPushButton("Login", uiWidget);
        connect(login_, SIGNAL(clicked()), this, SLOT(LoginClick()));

        init_layout_  = new QVBoxLayout();
        init_layout_->addWidget(user_id_);
        init_layout_->addWidget(login_);
        uiWidget->setLayout(init_layout_);
    }

    void CalmgramWindow::MainWindow(int id) {

        qDeleteAll(uiWidget->children());
        // слой с ID чата, кнопкой обновления и со списком чатов
        user_name_ = new QLabel("User: " + QString::number(id));
        user_name_->setWhatsThis(QString::number(id));
        chats_ = new QListWidget(uiWidget);
        std::vector<int> chats = user_->GetChats();
        for (size_t i = 0; i < chats.size(); i++) {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText("chat "+QString::number(chats[i]));
            item->setWhatsThis(QString::number(chats[i]));
            chats_->addItem(item);
        }
        connect(chats_,SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(ChatsItemClick(QListWidgetItem*)));
        refresh_ = new QPushButton("Refresh",uiWidget);
        connect(refresh_, SIGNAL(clicked()), this, SLOT(RefreshClick()));

        chats_layout_ = new QVBoxLayout();
        chats_layout_->addWidget(user_name_);
        chats_layout_->addWidget(chats_);
        chats_layout_->addWidget(refresh_);
        
        // слой с добавлением нового чата
        second_id_ = new QLineEdit(uiWidget);
        second_id_->setPlaceholderText("Friend ID...");
        add_chat_ = new QPushButton("Add chat",uiWidget);
        connect(add_chat_,SIGNAL(clicked()),this,SLOT(AddChatClick()));
        add_chat_layout_ = new QVBoxLayout();
        add_chat_layout_->addWidget(second_id_);
        add_chat_layout_->addWidget(add_chat_);

        //слой с ID чата и самим чатом
        chat_id_ = new QLabel("Chat: ");
        chat_id_->setWhatsThis("-1");
        chat_ = new QListWidget(uiWidget);
        connect(chat_,SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(MsgItemClick(QListWidgetItem*)));
        chat_layout_ = new QVBoxLayout();
        chat_layout_->addWidget(chat_id_);
        chat_layout_->addWidget(chat_);

        //слой отправки сообщения
        message_ = new QLineEdit(uiWidget);
        message_->setPlaceholderText("Msg...");
        send_msg_ = new QPushButton("Send",uiWidget);
        connect(send_msg_,SIGNAL(clicked()),this,SLOT(MsgSendClick()));

        send_msg_layout_ = new QHBoxLayout();
        send_msg_layout_->addWidget(message_);
        send_msg_layout_->addWidget(send_msg_);

        // финальное обьединение слоев
        layout_ = new QGridLayout();
        layout_->setSpacing(5);

        layout_->addLayout(chats_layout_, 0, 0, 2, 1);
        layout_->addLayout(add_chat_layout_, 2, 0, 1 , 1);
        layout_->addLayout(chat_layout_, 0, 2, 2, 2);
        layout_->addLayout(send_msg_layout_, 2, 2, 1, 1);

        uiWidget->setLayout(layout_);
    }

    void CalmgramWindow::Refresh(std::vector<int> const& updated_chats) {
        chats_->clear();
        std::vector<int> chats = user_->GetChats();
        if (chats.empty()) {
            chat_id_->setText("Chat: ");
            chat_id_->setWhatsThis("-1");
            chat_->clear();
        }
        for (auto chat : chats) {
            auto idx = std::find(updated_chats.begin(), updated_chats.end(), chat);
            QListWidgetItem *item = new QListWidgetItem;
            if (idx == updated_chats.end()) {
                item->setText("chat " + QString::number(chat));
            } else {
                if (chat != chat_id_->whatsThis().toInt()) {
                    item->setText("chat " + QString::number(chat) + "(*)");
                } else {
                    OpenChat();
                    item->setText("chat " + QString::number(chat));
                }
            }
            item->setWhatsThis(QString::number(chat));
            chats_->addItem(item);
        }
    }

    void CalmgramWindow::OpenChat() {
        chat_->clear();
        chat_id_->setText("Chat: "+ chat_id_->whatsThis());
        std::vector<entities::Message> msgs = user_->OpenChat(chat_id_->whatsThis().toInt());
        for (auto msg : msgs) {
            QListWidgetItem *item = new QListWidgetItem;
            if (msg.is_marked) {
                item->setText("user " + QString::number(msg.owner_id) + ":*censored*");
                item->setToolTip(QString::fromStdString(msg.content.data));
            } else {
                item->setText("user " + QString::number(msg.owner_id) + ": " + QString::fromStdString(msg.content.data));
            }
            item->setWhatsThis(QString::fromStdString(msg.content.data));
            chat_->addItem(item);
        }
    }

    void CalmgramWindow::LoginClick() {
        int id = user_id_->text().toInt();
        try {
            user_->Auth(id);
        } catch (std::exception const& e) {
            QMessageBox::warning(uiWidget,"Error", e.what());
            return;
        }
        MainWindow(id);
    }

    void CalmgramWindow::RefreshClick() {
        try
        {
            Refresh(user_->UpdateChats());
        }
        catch(const std::exception& e)
        {
            QMessageBox::warning(uiWidget,"Error",e.what());
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
        if(item->toolTip().isEmpty()) {
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
        std::cout << item->whatsThis().toStdString() << std::endl;
        // if(item->toolTip().isEmpty()) {
        //     user_->ReportAboutMark(item->whatsThis().toStdString(), true);
        // } else {
        //     user_->ReportAboutMark(item->whatsThis().toStdString(), false);
        // }
    }

    void CalmgramWindow::AddChatClick() {
        QListWidgetItem *item = new QListWidgetItem;
        try {        
            int chat_id = user_->CreateChat(std::vector<int> {second_id_->text().toInt()});
            item->setText("chat " + QString::number(chat_id));
            item->setWhatsThis(QString::number(chat_id));
            chats_->addItem(item);
        } catch(const std::exception& e) {
            QMessageBox::warning(uiWidget,"Error",e.what());
            return;
        }

    }

    void CalmgramWindow::MsgSendClick() {
        try
        {
            user_->SendMessage(message_->text().toStdString(), chat_id_->whatsThis().toInt());
            QListWidgetItem *item = new QListWidgetItem;    
            item->setText("user " + user_name_->whatsThis() + ": " + message_->text());
            item->setWhatsThis(message_->text());
            chat_->addItem(item);
        }
        catch(const std::exception& e)
        {
            QMessageBox::warning(uiWidget,"Error",e.what());
            return;
        }
    }
} // calmgram::api_client::user_interface
