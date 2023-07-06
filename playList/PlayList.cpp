//
// Created by juncheng on 2023/7/6.
//

#include "PlayList.h"
#include <QDebug>
#include <QStandardItemModel>

PlayList::PlayList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void PlayList::setupUI() {
    this->setStyleSheet("border-radius: 10px;background-color: transparent;border: 2px solid gray;");
    this->setMinimumSize(200, 400);
    mainLayout = new QVBoxLayout;
    playListView = new QListView;
    model=new QStandardItemModel;
    pbt_reload = new QPushButton("刷新");
    //
    connect(pbt_reload, &QPushButton::clicked, this, &PlayList::show_list);

    mainLayout->addWidget(pbt_reload);
    mainLayout->addWidget(playListView);
    this->setLayout(mainLayout);
}

QListView *PlayList::getPlayListView() const {
    return playListView;
}

const QString &PlayList::getCurrentPlayName() const {
    return currentPlayName;
}

void PlayList::setCurrentPlayName(const QString &currentPlayName) {
    PlayList::currentPlayName = currentPlayName;
}

const QVector<QString> &PlayList::getCurrentPlaylistName() const {
    return currentPlaylistName;
}

void PlayList::setCurrentPlaylistName(const QVector<QString> &currentPlaylistName) {
     PlayList::currentPlaylistName = currentPlaylistName;
}


void PlayList::show_list() {
    model->clear(); // 清空模型数据
    this->setCurrentPlaylistName(currentPlaylistName);
    // 重新添加数据
    for (const QString &name: currentPlaylistName) {
        auto *item = new QStandardItem(name);
        model->appendRow(item);
    }
    qDebug()<<currentPlaylistName<<"侧边栏";
    playListView->setModel(model); // 设置模型到视图中
}

void PlayList::setPlayListView(QListView *playListView) {
    PlayList::playListView = playListView;
}

const QVector<QString> &PlayList::getCurrentPlaylist() const {
    return currentPlaylist;
}

void PlayList::setCurrentPlaylist(const QVector<QString> &currentPlaylist) {
    PlayList::currentPlaylist = currentPlaylist;
}

const QVector<QString> &PlayList::getCurrentPlaylistLrc() const {
    return currentPlaylistLrc;
}

void PlayList::setCurrentPlaylistLrc(const QVector<QString> &currentPlaylistLrc) {
    PlayList::currentPlaylistLrc = currentPlaylistLrc;
}

const QString &PlayList::getCurrentPlay() const {
    return currentPlay;
}

void PlayList::setCurrentPlay(const QString &currentPlay) {
    PlayList::currentPlay = currentPlay;
}

const QString &PlayList::getCurrentPlayLrc() const {
    return currentPlayLrc;
}

void PlayList::setCurrentPlayLrc(const QString &currentPlayLrc) {
    PlayList::currentPlayLrc = currentPlayLrc;
}



PlayList::~PlayList() = default;