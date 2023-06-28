//
// Created by juncheng on 2023/6/28.
//

#include "FromNet.h"
FromNet::FromNet(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void FromNet::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: pink;");
}

FromNet::~FromNet() = default;