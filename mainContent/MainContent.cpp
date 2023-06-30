//
// Created by juncheng on 2023/6/27.
//

#include "MainContent.h"

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
    localMusicPage = new LocalMusic;
    playListPage = new PlayList;
    fromNetPage = new FromNet;
    contentPages = new QStackedWidget;
    contentPages->addWidget(localMusicPage);
    contentPages->addWidget(playListPage);
    contentPages->addWidget(fromNetPage);
    qhBoxLayout->addWidget(contentPages);
}

QStackedWidget *MainContent::getContentPages() const {
    return contentPages;
}

LocalMusic *MainContent::getLocalMusicPage() const {
    return localMusicPage;
}

void MainContent::setLocalMusicPage(LocalMusic *localMusicPage) {
    MainContent::localMusicPage = localMusicPage;
}

PlayList *MainContent::getPlayListPage() const {
    return playListPage;
}

void MainContent::setPlayListPage(PlayList *playListPage) {
    MainContent::playListPage = playListPage;
}

FromNet *MainContent::getFromNetPage() const {
    return fromNetPage;
}

void MainContent::setFromNetPage(FromNet *fromNetPage) {
    MainContent::fromNetPage = fromNetPage;
}

MainContent::~MainContent() = default;