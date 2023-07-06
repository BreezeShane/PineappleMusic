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
    favoriteListPage = new FavoriteList;
    fromNetPage = new FromNet;
    chatroomPage = new Chatroom;
    playListPage = new PlayList;
    contentPages = new QStackedWidget;
    contentPages->addWidget(favoriteListPage);
    contentPages->addWidget(localMusicPage);
    contentPages->addWidget(fromNetPage);
    contentPages->addWidget(chatroomPage);
    contentPages->addWidget(playListPage);
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



FromNet *MainContent::getFromNetPage() const {
    return fromNetPage;
}

void MainContent::setFromNetPage(FromNet *fromNetPage) {
    MainContent::fromNetPage = fromNetPage;
}

FavoriteList *MainContent::getFavoriteListPage() const {
    return favoriteListPage;
}

void MainContent::setFavoriteListPage(FavoriteList *favoriteListPage) {
    MainContent::favoriteListPage = favoriteListPage;
}

Chatroom *MainContent::getChatroomPage() const {
    return chatroomPage;
}

void MainContent::setChatroomPage(Chatroom *chatroomPage) {
    MainContent::chatroomPage = chatroomPage;
}

PlayList *MainContent::getPlayListPage() const {
    return playListPage;
}

void MainContent::setPlayListPage(PlayList *playListPage) {
    MainContent::playListPage = playListPage;
}

MainContent::~MainContent() = default;