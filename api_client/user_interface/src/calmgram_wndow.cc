//
// Created by Иван on 16.04.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_calmgram_wndow.h" resolved

#include "calmgram_window.h"
#include "ui_calmgram_window.h"

namespace calmgram::api_client::user_interface {
    CalmgramWindow::CalmgramWindow()
    :ui(new Ui::CalmgramWindow)
{
    user_id_= new QLineEdit();
    user_id_->setText("Enter user ID...");
    login_ = new QPushButton("&login", this);
    connect(login_, SIGNAL(clicked()), this, SLOT(LoginClick()));
    init_layout  = new QVBoxLayout();
    init_layout->addWidget(user_id_);
    init_layout->addWidget(login_);

    setLayout(init_layout);
}


CalmgramWindow::~CalmgramWindow()
{
    delete ui;
}

void CalmgramWindow::LoginClick() {
    int id = user_id_->text().toInt();
    
}

void CalmgramWindow::Update() {}

void CalmgramWindow::FillChats(std::vector<int> new_ids) {}

void CalmgramWindow::OpenChat(int chat_id) {}

std::string CalmgramWindow::PrintMessage(entities::Message msg) {
    std::string tmp;
    return tmp;
}

void CalmgramWindow::ChatClick() {}

void CalmgramWindow::ChatAddClick() {}

void CalmgramWindow::ImgClick() {}

void CalmgramWindow::MsgClick() {}

void CalmgramWindow::RefreshClick(){}

} // calmgram::api_client::user_interface
