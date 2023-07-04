//
// Created by juncheng on 2023/7/3.
//

#ifndef PINEAPPLEMUSIC_CHATROOM_H
#define PINEAPPLEMUSIC_CHATROOM_H

#include <QFrame>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QTcpSocket>
#include <QTcpServer>



class Chatroom : public QFrame
{
Q_OBJECT
private:
    QVBoxLayout *verticalLayout{};
    QListView *infoListView{};
    QHBoxLayout *horizontalLayout{};
    QPushButton *nickNameLabel{};
    QLineEdit *nickNameInput{};
    QLineEdit *messageInput{};
    QPushButton *pbtSend{};

    QTcpSocket *socket;
    QTcpSocket *client;

private slots:
    void newClent();

    void ClientDate();

    void info_Send();



public:
    explicit Chatroom(QWidget *parent = nullptr);
    void setupUI();

    void retranslateUi();

    void server_start();

    ~Chatroom() override;


};

#endif //PINEAPPLEMUSIC_CHATROOM_H
