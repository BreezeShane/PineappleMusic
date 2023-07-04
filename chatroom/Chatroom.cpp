//
// Created by juncheng on 2023/7/3.
//

#include "Chatroom.h"
#include <QDebug>
#include <QMessageBox>

Chatroom::Chatroom(QWidget *parent)
        : QFrame(parent) {

    setupUI();

    connect(pbtSend,&QPushButton::clicked,this,&Chatroom::info_Send);
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
}

void Chatroom::server_start() {
    socket = new QTcpSocket;
    //连接服务器
    QString ip = "43.139.97.111";
    QString port = "9090";
    socket->connectToHost(QHostAddress(ip),port.toUShort());

    connect(socket,&QTcpSocket::connected,[=](){
        QMessageBox::information(this,"连接提示","连接成功");
    });

    connect(socket,&QTcpSocket::disconnected,[=](){
        QMessageBox::information(this,"连接提示","连接断开");
    });

    connect(socket,&QTcpSocket::readyRead,this,&Chatroom::ClientDate);

    QByteArray data = QString(messageInput->text()).toUtf8();
    socket->write(data);

}

void Chatroom::newClent() {

}

//接收信息
void Chatroom::ClientDate() {
//    client = (QTcpSocket *)sender();
//    //ui->textEdit->append(QString(client->readAll()).toUtf8());
//    qDebug()<<QString(client->readAll())<<endl;

    qDebug()<<QString(socket->readAll())<<endl;
}

void Chatroom::info_Send() {
    server_start();
}
// retranslateUi



Chatroom::~Chatroom() = default;