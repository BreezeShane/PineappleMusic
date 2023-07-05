

#include <QStandardItemModel>
#include "FavoriteList.h"
#include <QTextStream>
#include <QDebug>
#include <QScrollArea>

FavoriteList::FavoriteList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void FavoriteList::setupUI() {
    qvBoxLayout=new QVBoxLayout();//垂直布局
    this->setStyleSheet("QWidget { border: 2px solid gray; border-radius: 10px; background-color: transparent; }");
    this->setContentsMargins(3, 3, 3, 3);
    refreshList =new QPushButton("刷新");
    deleteMyfPbt=new QPushButton("取消喜欢");
    refreshList->setFont(QFont("宋体", 13));
    deleteMyfPbt->setFont(QFont("宋体", 13));
    refreshList->setStyleSheet("QPushButton {"

                                "border: none;"
                                "border: 2px solid gray;"

                                "    padding: 4px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: #F5F5DC;"
                                "}"
                                "QPushButton:pressed {"
                               "background-color: #FFFFF0;"
                                "}");
    deleteMyfPbt->setStyleSheet("QPushButton {"

                               "border: none;"
                               "border: 2px solid gray;"

                               "    padding: 4px;"
                               "}"
                                "QPushButton:hover {"
                                "    background-color: #F5F5DC;"
                                "}"
                                "QPushButton:pressed {"
                                "background-color: #FFFFF0;"
                                "}");
    favoriteListView=new QListView();
    favoriteListView->setFont(QFont("宋体", 13));
    favoriteListView->setStyleSheet("QListView{padding:5px;}"
                                 "QListView::item{padding:5px;}");
    // 放置在 QScrollArea 中
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(favoriteListView);

    qvBoxLayout->addWidget(refreshList);
    qvBoxLayout->addWidget(scrollArea);
    qvBoxLayout->addWidget(deleteMyfPbt);
    this->setLayout(qvBoxLayout);
    updatePlayList();
    //点击刷新播放列表
    connect(refreshList, &QPushButton::clicked, this, &FavoriteList::playListUp);
    //点击取消喜欢
    connect(deleteMyfPbt, &QPushButton::clicked, this, &FavoriteList::deleteMyFavorite);
}
void FavoriteList::playListUp() {
    updatePlayList();
}
void FavoriteList::deleteMyFavorite() {
    // 获取选中音乐的索引
    QModelIndex selectedIndex = favoriteListView->currentIndex();

// 获取音乐信息
    QString selectedMusic = selectedIndex.data(Qt::DisplayRole).toString();
    qDebug()<<"wswdwd"<<selectedMusic<<endl;

// 从模型中删除选中的音乐
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(favoriteListView->model());
    model->removeRow(selectedIndex.row());

// 从m3u文件中删除对应的数据
    QFile musicPlaylist("../resource/favoriteListFile.m3u");
    if (musicPlaylist.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QString fileContent = QString::fromUtf8(musicPlaylist.readAll());
        // 查找选中音乐所在行的起始位置
        int startIndex = fileContent.indexOf(selectedMusic);

        // 查找选中音乐所在行的结束位置
        int endIndex = fileContent.indexOf('\n', startIndex);
        if (endIndex == -1) { // 如果选中音乐是文件的最后一行
            endIndex = fileContent.length();
        } else {
            endIndex++; // 包括行尾的换行符 \n
        }

        // 删除选中音乐整行数据
        fileContent.remove(startIndex, endIndex - startIndex);

        // 将更新后的内容重新写入文件
        musicPlaylist.seek(0);
        musicPlaylist.write(fileContent.toUtf8());
        musicPlaylist.resize(musicPlaylist.pos()); // 缩小文件大小以删除剩余内容
        musicPlaylist.close();
    }

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
                favoriteListLrc.push_back(parts[1]);
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