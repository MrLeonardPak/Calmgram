#include "calmgram_window.h"

namespace calmgram::api_client::user_interface {
 
    CalmgramWindow::CalmgramWindow(std::shared_ptr<use_case::IUserUC> user_uc)
        : user_(user_uc)
    {

        uiWidget = new QWidget( this );
        setCentralWidget( uiWidget );

        user_id_= new QLineEdit(uiWidget);
        user_id_->setText("Enter user ID...");
        login_ = new QPushButton("&login", uiWidget);
        connect(login_, SIGNAL(clicked()), this, SLOT(LoginClick()));

        init_layout_  = new QVBoxLayout();
        init_layout_->addWidget(user_id_);
        init_layout_->addWidget(login_);
        uiWidget->setLayout(init_layout_);

    }

    CalmgramWindow::~CalmgramWindow()
    {
        delete user_id_;
        delete login_;
        delete init_layout_;
    }


    void CalmgramWindow::LoginClick() {
        int id = user_id_->text().toInt();
        try {
            user_->Auth(id);
        } catch (std::exception const& e) {
            user_id_->setText(e.what());
        }

        delete init_layout_;
        qDeleteAll(uiWidget->children());

        // слой с ID чата, кнопкой обновления и со списком чатов
        user_name_ = new QLabel("User: " + QString::number(id));
        chats_ = new QListWidget(uiWidget);
        std::vector<int> chats = user_->GetChats();
        for (size_t i = 0; i < chats.size(); i++) {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText("chat "+QString::number(chats[i]));
            chats_->addItem(item);
        }
        connect(chats_,SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(ChatItemClicked(QListWidgetItem*)));
        refresh_ = new QPushButton("&refresh",uiWidget);
        connect(refresh_, SIGNAL(clicked()), this, SLOT(RefreshClick()));

        chats_layout_ = new QVBoxLayout();
        chats_layout_->addWidget(user_name_);
        chats_layout_->addWidget(chats_);
        chats_layout_->addWidget(refresh_);

        // слой с добавлением новго чата
        second_id_ = new QLineEdit(uiWidget);
        second_id_->setText("Friend ID...");
        add_chat_ = new QPushButton("&Add chat",uiWidget);
        connect(add_chat_,SIGNAL(clicked()),this,SLOT(AddChatClick()));

        add_chat_layout_ = new QVBoxLayout();
        add_chat_layout_->addWidget(second_id_);
        add_chat_layout_->addWidget(add_chat_);

        //слой с ID чата и самим чатом
        opened_chat_id_ = -1;
        chat_id_ = new QLabel("Chat: "+ QString::number(opened_chat_id_));
        chat_ = new QListWidget(uiWidget);
        std::vector<entities::Message> msgs = user_->OpenChat(opened_chat_id_);
        for (size_t i = 0; i < chats.size(); i++) {
            QListWidgetItem *item = new QListWidgetItem;
            if (msgs[i].is_marked) {
                item->setText("user " + QString::number(msgs[i].owner_id) + ":*censored*");
    //             qDebug() << "censor ";
            } else {
                item->setText("user " + QString::number(msgs[i].owner_id) + ":" + QString::fromStdString(msgs[i].content.data));
    //            qDebug() << "uncenor";
            }
            chat_->addItem(item);
        }

        chat_layout_ = new QVBoxLayout();
        chat_layout_->addWidget(chat_id_);
        chat_layout_->addWidget(chat_);

        //слой отправки сообщения
        message_ = new QLineEdit(uiWidget);
        message_->setText("Msg...");
        send_img_ = new QPushButton("&Send img",uiWidget);
        connect(send_img_,SIGNAL(clicked()),this,SLOT(ImgClick()));
        send_msg_ = new QPushButton("&Send",uiWidget);
        connect(send_msg_,SIGNAL(clicked()),this,SLOT(MsgClick()));

        send_msg_layout_ = new QHBoxLayout();
        send_msg_layout_->addWidget(message_);
        send_msg_layout_->addWidget(send_img_);
        send_msg_layout_->addWidget(send_msg_);

        // финальное обьединение слоев
        layout_ = new QGridLayout();
        layout_->setSpacing(5);

        layout_->addLayout(chats_layout_,0,0);
        layout_->addLayout(add_chat_layout_,1,0,2,1);
        layout_->addLayout(chat_layout_,0,1,1,2);
        layout_->addLayout(send_msg_layout_,1,1,2,2);

        uiWidget->setLayout(layout_);

    }

    void CalmgramWindow::RefreshClick() {
        // .....

    }


    void CalmgramWindow::ChatItemClicked(QListWidgetItem* item) {
        // .....

    }

    void CalmgramWindow::AddChatClick() {
        // .....

    }

    void CalmgramWindow::ImgClick() {
        // .....

    }

    void CalmgramWindow::MsgClick() {
        // .....

    }
} // calmgram::api_client::user_interface
