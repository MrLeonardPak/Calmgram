//
// Created by Иван on 16.04.2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_calmgram_wndow.h" resolved

#include "calmgram_window.h"
#include "ui_calmgram_window.h"

namespace calmgram::api_client::user_interface {
    calmgram_wndow::CalmgramWindow(QWidget *parent) :
            QWidget(parent), ui(new Ui::CalmgramWindow) {
        ui->setupUi(this);
    }

    calmgram_wndow::~CalmgramWindow() {
        delete ui;
    }

    void LoginClick() {}

    void Update() {}

    void FillChats(std::vector<int> new_ids) {}

    void OpenChat(int chat_id) {}

    std::string PrintMessage(entities::Message msg) {
        std::string tmp;
        return tmp;
    }

    void ChatClick() {}

    void ChatAddClick() {}

    void ImgClick() {}

    void MsgClick() {}

    void RefreshClick(){}

} // calmgram::api_client::user_interface
