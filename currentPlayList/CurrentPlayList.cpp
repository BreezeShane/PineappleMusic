//
// Created by juncheng on 2023/7/6.
//

#include "CurrentPlayList.h"
#include <QDebug>
#include <QStandardItemModel>

CurrentPlayList::CurrentPlayList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void CurrentPlayList::setupUI() {
    this->setStyleSheet("border-radius: 10px;");
    this->setMinimumSize(200, 400);
    mainLayout = new QVBoxLayout;
    playListView = new QListView;

    mainLayout->addWidget(playListView);
    this->setLayout(mainLayout);
}

QListView *CurrentPlayList::getPlayListView() const {
    return playListView;
}

const QString &CurrentPlayList::getCurrentPlayName() const {
    return currentPlayName;
}

void CurrentPlayList::setCurrentPlayName(const QString &currentPlayName) {
    CurrentPlayList::currentPlayName = currentPlayName;
}

const QVector<QString> &CurrentPlayList::getCurrentPlaylistName() const {
    return currentPlaylistName;
}

void CurrentPlayList::setCurrentPlaylistName(const QVector<QString> &currentPlaylistName) {
    CurrentPlayList::currentPlaylistName = currentPlaylistName;
}

void CurrentPlayList::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    auto *model = new QStandardItemModel;
    for (const QString &name: currentPlaylistName) {
        auto *item = new QStandardItem(name);
        model->appendRow(item);
    }
    playListView->setModel(model);
}

void CurrentPlayList::hideEvent(QHideEvent *event) {
    QWidget::hideEvent(event);
    qDebug() << "hide play list";
}

void CurrentPlayList::setPlayListView(QListView *playListView) {
    CurrentPlayList::playListView = playListView;
}

const QVector<QString> &CurrentPlayList::getCurrentPlaylist() const {
    return currentPlaylist;
}

void CurrentPlayList::setCurrentPlaylist(const QVector<QString> &currentPlaylist) {
    CurrentPlayList::currentPlaylist = currentPlaylist;
}

const QVector<QString> &CurrentPlayList::getCurrentPlaylistLrc() const {
    return currentPlaylistLrc;
}

void CurrentPlayList::setCurrentPlaylistLrc(const QVector<QString> &currentPlaylistLrc) {
    CurrentPlayList::currentPlaylistLrc = currentPlaylistLrc;
}

const QString &CurrentPlayList::getCurrentPlay() const {
    return currentPlay;
}

void CurrentPlayList::setCurrentPlay(const QString &currentPlay) {
    CurrentPlayList::currentPlay = currentPlay;
}

const QString &CurrentPlayList::getCurrentPlayLrc() const {
    return currentPlayLrc;
}

void CurrentPlayList::setCurrentPlayLrc(const QString &currentPlayLrc) {
    CurrentPlayList::currentPlayLrc = currentPlayLrc;
}

CurrentPlayList::~CurrentPlayList() = default;