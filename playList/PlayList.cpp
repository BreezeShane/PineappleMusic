//
// Created by juncheng on 2023/6/27.
//

#include "PlayList.h"
PlayList::PlayList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void PlayList::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: red;");
}

PlayList::~PlayList() = default;