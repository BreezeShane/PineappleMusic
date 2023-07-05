

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
    playMusicPbt->setStyleSheet("padding:5px;");
    playMusicPbt->setFont(QFont("宋体", 13));
    playListView=new QListView();
    playListView->setFont(QFont("宋体", 13));

    playLayout->addWidget(playMusicPbt);
    playLayout->addWidget(playListView);
    playLayout->addWidget(text);
    this->setLayout(playLayout);
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