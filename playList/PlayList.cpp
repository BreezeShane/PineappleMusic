

#include <QStandardItemModel>
#include "PlayList.h"
#include <QTextStream>
#include <QDebug>
PlayList::PlayList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void PlayList::setupUI() {
    playLayout=new QVBoxLayout();//垂直布局
    this->setStyleSheet("border: 2px solid gray;border-radius:10px;background-color: transparent");
    this->setContentsMargins(3, 3, 3, 3);
    playMusicPbt =new QPushButton("播放");
    playMusicPbt->setFont(QFont("宋体", 13));
    playMusicPbt->setStyleSheet("QPushButton {"
                                "background-color: #555555;"
                                "border: none;"
                                "color: white;"
                                "    padding: 4px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: gray;"
                                "}"
                                "QPushButton:pressed {"
                                "    background-color:gray ;"
                                "}");
    playListView=new QListView();
    playListView->setFont(QFont("宋体", 13));

    playLayout->addWidget(playMusicPbt);
    playLayout->addWidget(playListView);
    playLayout->addWidget(text);
    this->setLayout(playLayout);
    updatePlayList();
    //点击刷新播放列表
    connect(playMusicPbt, &QPushButton::clicked, this, &PlayList::playListUp);
}
void PlayList::playListUp() {
    updatePlayList();
}
void PlayList::updatePlayList() {
    qDebug()<<"hhh"<<endl;
    QFile musicPlaylistFile ("../resource/musicPlaylist.m3u");
    auto *model = new QStandardItemModel;
    playListView->setModel(model);
    if (!musicPlaylistFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open playlist file for reading.";
        return;
    }
    QTextStream in(&musicPlaylistFile);
    in.setCodec("UTF-8");
    QStringList titleLines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) {
            if (line.startsWith("#")) {
                titleLines << line;
            } else if (line.startsWith("lrc#")) {
                QStringList parts = line.split(QRegExp("#"));
                musicPlayLrc << parts[1];
            } else {
                musicPlay.push_back(line);
            }
        }
    }

    // 添加歌曲信息到模型中
    for (const QString &line: titleLines) {
        QStringList parts = line.split(QRegExp(":"));
        if (parts.size() == 2) {
//            QString artist = parts[0];
//            QString title = parts[1];
            QString title = parts[1];
            auto *item = new QStandardItem(title);
            model->appendRow(item);
        }
    }
    musicPlaylistFile.close();
}

const QVector<QString> &PlayList::getMusicPlay() const {
    return musicPlay;
}

void PlayList::setMusicPlay(const QVector<QString> &musicPlay) {
    PlayList::musicPlay = musicPlay;
}

QListView *PlayList::getPlayListView() const {
    return playListView;
}

void PlayList::setPlayListView(QListView *playListView) {
    PlayList::playListView = playListView;
}

const QVector<QString> &PlayList::getMusicPlayLrc() const {
    return musicPlayLrc;
}

void PlayList::setMusicPlayLrc(const QVector<QString> &musicPlayLrc) {
    PlayList::musicPlayLrc = musicPlayLrc;
}

PlayList::~PlayList() = default;