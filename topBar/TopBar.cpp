//
// Created by juncheng on 2023/6/27.
//

#include "TopBar.h"
TopBar::TopBar(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void TopBar::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: yellow;");
    this->setFixedHeight(100);
}

TopBar::~TopBar() = default;