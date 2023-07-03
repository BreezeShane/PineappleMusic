//
// Created by juncheng on 2023/7/3.
//

#ifndef PINEAPPLEMUSIC_CHATROOM_H
#define PINEAPPLEMUSIC_CHATROOM_H

#include <QFrame>

class Chatroom : public QFrame
{
Q_OBJECT
public:
    explicit Chatroom(QWidget *parent = nullptr);
    void setupUI();

    ~Chatroom() override;
};

#endif //PINEAPPLEMUSIC_CHATROOM_H
