//
// Created by juncheng on 2023/6/27.
//

#include "MainContent.h"

MainContent::MainContent(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void MainContent::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: pink;");
}

MainContent::~MainContent() = default;