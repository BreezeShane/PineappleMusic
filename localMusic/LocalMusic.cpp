//
// Created by juncheng on 2023/6/27.
//

#include "LocalMusic.h"
LocalMusic::LocalMusic(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void LocalMusic::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: green;");
}

LocalMusic::~LocalMusic() = default;