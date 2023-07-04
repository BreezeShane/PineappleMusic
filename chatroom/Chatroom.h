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
public:
    explicit Chatroom(QWidget *parent = nullptr);
    void setupUI();
    void retranslateUi();
    ~Chatroom() override;
};

#endif //PINEAPPLEMUSIC_CHATROOM_H
