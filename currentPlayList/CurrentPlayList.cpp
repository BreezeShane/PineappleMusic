//
// Created by juncheng on 2023/7/6.
//

#include "CurrentPlayList.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QFileDialog>

CurrentPlayList::CurrentPlayList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void CurrentPlayList::setupUI() {
    this->setStyleSheet("border-radius: 10px;");
    this->setMinimumSize(200, 400);
    mainLayout = new QVBoxLayout;
    playListView = new QListView;
    playListView->setStyleSheet("background-color: transparent;");
    saveLocal=new QPushButton("保存");
    mainLayout->addWidget(playListView);
    mainLayout->addWidget(saveLocal);

    // 设置背景图的样式
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(QPixmap("../resource/image/4.jpg")));
    this->setPalette(palette);
    this->setLayout(mainLayout);
    connect(saveLocal, &QPushButton::clicked, this, &CurrentPlayList::saveCurrentMusic);

}
void CurrentPlayList::saveCurrentMusic() {
    QModelIndex index = playListView->currentIndex();
    int row = index.row();
    currentPlay = currentPlaylist[row];

    // 创建文件对话框，让用户选择保存的文件路径和名称
    QString filePath = QFileDialog::getSaveFileName(this, "Save Music", "", "Music Files (*.mp3)");

    // 检查用户是否选择了文件路径
    if (!filePath.isEmpty()) {
        QFile file(filePath);

        if (file.open(QIODevice::WriteOnly)) {
            file.write(currentPlay.toUtf8());
            file.close();
            qDebug() << "Music saved to" << filePath;
        } else {
            qDebug() << "Failed to open file for writing.";
        }
    }
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