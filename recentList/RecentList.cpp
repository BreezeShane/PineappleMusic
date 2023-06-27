//
// Created by juncheng on 2023/6/27.
//

#include "RecentList.h"
RecentList::RecentList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void RecentList::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: red;");
}

RecentList::~RecentList() = default;