//
// Created by juncheng on 2023/7/3.
//

#include "Chatroom.h"
Chatroom::Chatroom(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void Chatroom::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: yellow;");
}

Chatroom::~Chatroom() = default;