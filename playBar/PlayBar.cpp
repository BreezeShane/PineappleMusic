//
// Created by juncheng on 2023/6/27.
//

#include "PlayBar.h"

PlayBar::PlayBar(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void PlayBar::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: green;");
    this->setFixedHeight(100);
}

PlayBar::~PlayBar() = default;