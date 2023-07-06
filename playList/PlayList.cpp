//
// Created by juncheng on 2023/7/6.
//

#include "PlayList.h"
PlayList::PlayList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void PlayList::setupUI() {
    this->setStyleSheet("border: 2px solid gray; border-radius: 10px; background-color: yellow; ");

}


PlayList::~PlayList() = default;