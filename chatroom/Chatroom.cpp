//
// Created by juncheng on 2023/7/3.
//

#include "Chatroom.h"
#include <QDebug>
Chatroom::Chatroom(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void Chatroom::setupUI() {
    this->setStyleSheet("border-radius: 10px;");

    verticalLayout = new QVBoxLayout();
    infoListView = new QListView();

    verticalLayout->addWidget(infoListView);

    horizontalLayout = new QHBoxLayout();
    nickNameLabel = new QPushButton();
    nickNameLabel->setFixedSize(32,32);
    nickNameLabel->setEnabled(false);
    horizontalLayout->addWidget(nickNameLabel);

    nickNameInput = new QLineEdit();
    nickNameInput->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    nickNameInput->setFixedHeight(32);
    horizontalLayout->addWidget(nickNameInput);

    messageInput = new QLineEdit();
    messageInput->setFixedHeight(32);
    horizontalLayout->addWidget(messageInput);

    pbtSend = new QPushButton();
    pbtSend->setFixedWidth(50);
    qDebug()<<pbtSend->styleSheet();
    horizontalLayout->addWidget(pbtSend);

    verticalLayout->addLayout(horizontalLayout);
    this->setLayout(verticalLayout);
    retranslateUi();
}// setupUi

void Chatroom::retranslateUi() {
    this->setWindowTitle(QApplication::translate("Frame", "Frame", nullptr));
//    nickNameLabel->setText("nickName");
    nickNameLabel->setIcon(QIcon("../resource/icon/nickname.svg"));
//    pbtSend->setText("发送");
    pbtSend->setIcon(QIcon("../resource/icon/send.svg"));
}// retranslateUi


Chatroom::~Chatroom() = default;