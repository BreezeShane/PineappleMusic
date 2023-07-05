

#include <QStandardItemModel>
#include "FavoriteList.h"
#include <QTextStream>
#include <QDebug>
FavoriteList::FavoriteList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void FavoriteList::setupUI() {
    qvBoxLayout=new QVBoxLayout();//垂直布局
    this->setStyleSheet("border: 2px solid gray;border-radius:10px;background-color: transparent");
    this->setContentsMargins(3, 3, 3, 3);
    refreshList =new QPushButton("刷新");
    refreshList->setFont(QFont("宋体", 13));
    refreshList->setStyleSheet("QPushButton {"
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
    favoriteListView=new QListView();
    favoriteListView->setFont(QFont("宋体", 13));

    qvBoxLayout->addWidget(refreshList);
    qvBoxLayout->addWidget(favoriteListView);
    qvBoxLayout->addWidget(text);
    this->setLayout(qvBoxLayout);
    updatePlayList();
    //点击刷新播放列表
    connect(refreshList, &QPushButton::clicked, this, &FavoriteList::playListUp);
}
void FavoriteList::playListUp() {
    updatePlayList();
}
void FavoriteList::updatePlayList() {
    QFile musicPlaylistFile ("../resource/favoriteListFile.m3u");
    auto *model = new QStandardItemModel;
    favoriteListView->setModel(model);
    if (!musicPlaylistFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open favoriteList file for reading.";
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
                favoriteListLrc << parts[1];
            } else {
                favoriteList.push_back(line);
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

const QVector<QString> &FavoriteList::getFavoriteList() const {
    return favoriteList;
}

void FavoriteList::setFavoriteList(const QVector<QString> &musicPlay) {
    FavoriteList::favoriteList = musicPlay;
}

QListView *FavoriteList::getFavoriteListView() const {
    return favoriteListView;
}

void FavoriteList::setFavoriteListView(QListView *playListView) {
    FavoriteList::favoriteListView = playListView;
}

const QVector<QString> &FavoriteList::getFavoriteListLrc() const {
    return favoriteListLrc;
}

void FavoriteList::setFavoriteListLrc(const QVector<QString> &musicPlayLrc) {
    FavoriteList::favoriteListLrc = musicPlayLrc;
}

FavoriteList::~FavoriteList() = default;