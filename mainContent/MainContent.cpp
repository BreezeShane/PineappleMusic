//
// Created by juncheng on 2023/6/27.
//

#include "MainContent.h"
#include "localMusic/LocalMusic.h"
#include "playList/PlayList.h"
#include "fromNet/FromNet.h"

MainContent::MainContent(QWidget *parent)
        : QFrame(parent) {

    setupUI();
    initContentPages();
}

void MainContent::setupUI() {
    qhBoxLayout = new QHBoxLayout;
    qhBoxLayout->setContentsMargins(0,0,0,0);    //去除外边距
    this->setLayout(qhBoxLayout);
}

void MainContent::initContentPages() {
    contentPages = new QStackedWidget;
    contentPages->addWidget(new LocalMusic);
    contentPages->addWidget(new PlayList);
    contentPages->addWidget(new FromNet);
    qhBoxLayout->addWidget(contentPages);
}

QStackedWidget *MainContent::getContentPages() const {
    return contentPages;
}

MainContent::~MainContent() = default;