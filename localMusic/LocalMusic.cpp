//
// Created by juncheng on 2023/6/27.
//

#include <QFileDialog>
#include <QTextStream>
//#include <QDebug>
#include <QDirIterator>
#include <QJsonArray>
#include <QJsonObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QJsonDocument>
#include <QStandardItemModel>
#include "LocalMusic.h"

LocalMusic::LocalMusic(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void LocalMusic::setupUI() {
    this->setStyleSheet("border: 2px solid gray;border-radius:10px;");
    this->setContentsMargins(3, 3, 3, 3);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    horizontalLayout = new QHBoxLayout();
    horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    reloadMusicPbt = new QPushButton(this);
    reloadMusicPbt->setStyleSheet("padding:5px;");
    reloadMusicPbt->setEnabled(true);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(reloadMusicPbt->sizePolicy().hasHeightForWidth());
    reloadMusicPbt->setSizePolicy(sizePolicy);
    reloadMusicPbt->setLayoutDirection(Qt::LeftToRight);

    horizontalLayout->addWidget(reloadMusicPbt);


    verticalLayout->addLayout(horizontalLayout);

    musicListView = new QListView(this);
    musicListView->setFont(QFont("宋体", 13));
    musicListView->setStyleSheet("QListView{padding:5px;}"
                                 "QListView::item{padding:5px;}"
    );
    verticalLayout->addWidget(musicListView);
    playlistFile = new QFile("../resource/playlist.m3u");

    connect(reloadMusicPbt, SIGNAL(clicked()), this, SLOT(scanLocalMusic()));
    updateMusicList();
    retranslateUi();
}

void LocalMusic::retranslateUi() {
    reloadMusicPbt->setText("重新扫描");
    reloadMusicPbt->setIcon(QIcon("../resource/icon/search.svg"));
} // retranslateUi

void LocalMusic::scanLocalMusic() {
    // 创建一个QMediaPlayer对象
    // 创建一个文件对话框，让用户选择要扫描的目录
    QString scanPath = QFileDialog::getExistingDirectory(nullptr, "Select Directory", QDir::homePath());

    if (!playlistFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open playlist file for writing.";
        return;
    }

    // 遍历目录中的所有文件
    QDir dir(scanPath);
    QStringList filters;
    filters << "*.mp3" << "*.m4a" << "*.ogg" << "*.flac";
    dir.setNameFilters(filters);
    QFileInfoList fileList = dir.entryInfoList();
    for (const QFileInfo &fileInfo: fileList) {
        // 获取文件元数据
        QMediaPlayer player;
        player.setMedia(QUrl::fromLocalFile(fileInfo.filePath()));
//        auto duration = player.metaData("Duration").toInt();
//        auto artist = player.metaData("Author").toString();
//        auto title = player.metaData("Title").toString();

        // 将元数据写入m3u文件中
        QTextStream out(playlistFile);
//        out << "#EXTINF:-1," << artist << " - " << title << "\n";
        out << "#EXTINF:" << fileInfo.fileName() << endl;
        out << fileInfo.filePath() << endl;
    }

    playlistFile->close();
    updateMusicList();
}

void LocalMusic::updateMusicList() {
    auto* model = new QStandardItemModel;
    musicListView->setModel(model);
    if (!playlistFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open playlist file for reading.";
        return ;
    }
    QTextStream in(playlistFile);
    QStringList titleLines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) {
            if (line.startsWith("#")){
                titleLines << line;
            } else{
                playList.append(line);
            }
        }
    }

    // 添加歌曲信息到模型中
    for (const QString &line : titleLines) {
        QStringList parts = line.split(QRegExp(":"));
        if (parts.size() == 2) {
//            QString artist = parts[0];
//            QString title = parts[1];
            QString title = parts[1];
            auto *item = new QStandardItem(title);
            model->appendRow(item);
        }
    }
    playlistFile->close();
}

QListView *LocalMusic::getMusicListView() const {
    return musicListView;
}

const QList<QString> &LocalMusic::getPlayList() const {
    return playList;
}

LocalMusic::~LocalMusic() = default;