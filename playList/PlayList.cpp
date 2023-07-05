

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
    QFile musicPlaylist ("../resource/musicPlaylist.m3u");
    auto *model = new QStandardItemModel;
    playListView->setModel(model);

    if(!musicPlaylist.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Failed to open file";
        return ;
    }
    QTextStream in(&musicPlaylist);
    QStringList titleLines;
    while (!in.atEnd()) {
        QString line = in.readLine();

        if (!line.isEmpty()) {
            if (line.startsWith("#")){
                titleLines << line;
            } else{
                musicPlay.push_back(line);
            }
        }
    }

    // 添加歌曲信息到模型中
    for (const QString &line : titleLines) {
        QStringList parts = line.split(QRegExp(":"));
        if (parts.size() == 2) {
            QString title = parts[1];
            auto *item = new QStandardItem(title);

            model->appendRow(item);
        }
    }
    musicPlaylist.close();
}
    PlayList::~PlayList() = default;