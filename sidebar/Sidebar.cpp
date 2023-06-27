//
// Created by juncheng on 2023/6/27.
//

#include "Sidebar.h"

Sidebar::Sidebar(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void Sidebar::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: red;");
    this->setFixedWidth(200);
}

Sidebar::~Sidebar() = default;
