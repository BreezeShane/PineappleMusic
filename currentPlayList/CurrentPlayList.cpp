//
// Created by juncheng on 2023/7/6.
//

#include "CurrentPlayList.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMessageBox>

CurrentPlayList::CurrentPlayList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void CurrentPlayList::setupUI() {
    this->setStyleSheet("border-radius: 10px;");
    this->setMinimumSize(200, 400);
    //标题
    this->setWindowTitle("播放列表");
    this->setWindowIcon(QIcon("../resource/icon/play.svg"));
    mainLayout = new QVBoxLayout;
    playListView = new QListView;
    playListView->setStyleSheet("background-color: transparent;");
    saveLocal=new QPushButton("保存");
    saveLocal->setStyleSheet("QPushButton{""border: 2px solid gray;"
                                            "    padding: 4px;"
                                            "}"
                                            "QPushButton:hover {"
                                            "    background-color: #F5F5DC;"
                                            "}"
                                            "QPushButton:pressed {"
                                            "background-color: #FFFFF0;"
                                            "}");
    mainLayout->addWidget(playListView);
    mainLayout->addWidget(saveLocal);

    // 设置背景图的样式
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(QPixmap("../resource/image/4.jpg")));
    this->setPalette(palette);
    this->setLayout(mainLayout);
    connect(saveLocal, &QPushButton::clicked, this, &CurrentPlayList::saveCurrentMusic);

}
void CurrentPlayList::saveCurrentMusic()
{
    QModelIndex index = playListView->currentIndex();
    int row = index.row();
    currentPlay = currentPlaylist[row];
    QString sourceFilePath = currentPlay;  // 获取当前音乐的原始文件路径
    QString destinationFolderPath = QFileDialog::getExistingDirectory(nullptr, "Select Destination Folder", QDir::homePath());
    if (destinationFolderPath.isNull()) {
        QMessageBox::information(this, "提示", "请选择目标文件夹");
        return;
    }
    QFileInfo fileInfo(sourceFilePath);
    QString destinationFilePath = destinationFolderPath + "/" + fileInfo.fileName();
    // 打开当前音乐文件
    QFile sourceFile(sourceFilePath);
    if (!sourceFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "错误", "无法打开音乐文件");
        return;
    }
    // 创建目标文件并打开以进行写入
    QFile destinationFile(destinationFilePath);
    if (!destinationFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "错误", "无法创建目标文件");
        return;
    }
    // 读取源文件并将数据写入目标文件
    QByteArray data = sourceFile.readAll();
    destinationFile.write(data);
    // 关闭文件
    sourceFile.close();
    destinationFile.close();
    QMessageBox::information(this, "提示", "音乐已保存到目标文件夹");
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