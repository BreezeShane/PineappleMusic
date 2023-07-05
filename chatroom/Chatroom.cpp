//
// Created by juncheng on 2023/7/3.
//
#include "Chatroom.h"
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QDateTime>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QScrollBar>

Chatroom::Chatroom(QWidget *parent)
        : QFrame(parent) {

    setupUI();
    model = new QStandardItemModel(infoListView);
    scrollBar = new QScrollBar;
    scrollBar = infoListView->verticalScrollBar();
    //发送按钮监听
    connect(pbtSend,&QPushButton::clicked,this,&Chatroom::info_Send);
    //连接按钮监听
    connect(join,&QPushButton::clicked,this,&Chatroom::on_join_clicked);
}

void Chatroom::setupUI() {
    this->setStyleSheet("border-radius: 10px;");
    //主布局
    verticalLayout = new QVBoxLayout();
    //顶层布局
    top_layout = new QHBoxLayout;
    top_layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    join = new QPushButton("");
    join->setFixedSize(82,32);
    join->setStyleSheet("border-radius: 10px;border: 1px solid gray");
    top_layout->addWidget(join);
    //加入主布局
    verticalLayout->addLayout(top_layout);

    //消息显示框
    infoListView = new QListView();
    infoListView->setFont(QFont("Arial", 14));
    verticalLayout->addWidget(infoListView);

    //消息发送布局
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
    horizontalLayout->addWidget(pbtSend);

    verticalLayout->addLayout(horizontalLayout);
    this->setLayout(verticalLayout);
    retranslateUi();
}// setupUi

void Chatroom::retranslateUi() {
    //设置图标
    this->setWindowTitle(QApplication::translate("Frame", "Frame", nullptr));
    nickNameLabel->setIcon(QIcon("../resource/icon/nickname.svg"));
    pbtSend->setIcon(QIcon("../resource/icon/send.svg"));

    //初始设置为未连接
    join->setIcon(QIcon("../resource/icon/disconnection.svg"));
    connet = false;
}

//接收信息
void Chatroom::ClientDate() {
    //接收服务器消息
    QByteArray data = socket->readAll();
    QString response = QString::fromUtf8(data);
    qDebug() << "Received response:" << response;
    //对接收的消息拆分
    QStringList parts = response.split(":");
    QString name = parts[0];
    QString info = parts[1];
    QString message = name + "  :\n     " + info+"\n";

    //在listview中显示
    QStandardItem *item2 = new QStandardItem(message);
    item2->setTextAlignment(Qt::AlignLeft);
    model->appendRow(item2);
    infoListView->setModel(model);
    scrollBar->setValue(scrollBar->maximum());

}
//发送按钮槽函数
void Chatroom::info_Send() {
    if(!connet) return ;
    server_start();
}
//发送消息
void Chatroom::server_start() {
    //获取昵称和输入框的消息,拼接成完整的字符串
    QString name = nickNameInput->text();
    QString message = messageInput->text();

    if (name.isEmpty() || message.isEmpty()) {
        return ;
    }
    QString information = name + " : " + message;
    QByteArray data = QString(information).toUtf8();
    //获取当前时间
    QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
    QString str = datatime->toString("yyyy-MM-dd hh:mm:ss ddd");    //设置时间格式
    QString strSend = str + "  " + name + ":" + "\n" + data;
    //发送
    qDebug() << "Received response:" << strSend;
    socket->write(data);

//    QStringList parts = information.split(":");
//    QString myname = parts[0];
//    QString myinfo = parts[1];
//    QString send_message = name +"      "+ ":\n \n " + myinfo+"     \n";

    //在listview中显示
    QStandardItem *item1 = new QStandardItem(information);
    item1->setTextAlignment(Qt::AlignRight);
    model->appendRow(item1);
    infoListView->setModel(model);
    scrollBar->setValue(scrollBar->maximum());
}

//连接服务器槽函数
void Chatroom::on_join_clicked() {
    connet = !connet;
    if(connet == true){
        join->setIcon(QIcon("../resource/icon/connection.svg"));
        socket = new QTcpSocket;
        //连接服务器
        QString ip = "43.139.97.111";
        //QString ip = "10.33.36.245";
        QString port = "9090";
        socket->connectToHost(QHostAddress(ip),port.toUShort());

        connect(socket, &QTcpSocket::stateChanged, this, [=](QAbstractSocket::SocketState state) {
            if (state == QAbstractSocket::ConnectedState) {
                // 连接成功，做出提示

                qDebug() << "Connected to server";

            } else if (state == QAbstractSocket::UnconnectedState) {
                if (socket->error() == QAbstractSocket::RemoteHostClosedError) {
                    // 服务器已断开，做出提示

                    qDebug() << "Server has disconnected";

                } else {
                    // 连接失败，做出提示

                    qDebug() << "Failed to connect to server:" << socket->errorString();

                }
            }
        });
        //启动监听
        connect(socket,&QTcpSocket::readyRead,this,&Chatroom::ClientDate);

        connect(socket,&QTcpSocket::connected,[=](){
            QMessageBox::information(this,"连接提示","连接成功");
        });

    }else{
        join->setIcon(QIcon("../resource/icon/disconnection.svg"));
        if (socket->state() == QAbstractSocket::ConnectedState) {
            socket->abort();
            QMessageBox::information(this,"连接提示","连接已断开");
        }
    }
}
// retranslateUi

void Chatroom::newClent() {

}


Chatroom::~Chatroom() = default;