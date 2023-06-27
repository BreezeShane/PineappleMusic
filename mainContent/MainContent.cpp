//
// Created by juncheng on 2023/6/27.
//

#include "MainContent.h"
#include "localMusic/LocalMusic.h"
#include "recentList/RecentList.h"

MainContent::MainContent(QWidget *parent)
        : QFrame(parent) {

    setupUI();
    initContentPages();
}

void MainContent::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: pink;");
    qhBoxLayout = new QHBoxLayout;
    this->setLayout(qhBoxLayout);
}

void MainContent::initContentPages() {
    contentPages = new QStackedWidget;
    contentPages->addWidget(new LocalMusic);
    contentPages->addWidget(new RecentList);
    qhBoxLayout->addWidget(contentPages);
}

MainContent::~MainContent() = default;