

#include <QStandardItemModel>
#include "FavoriteList.h"
#include <QTextStream>
#include <QDebug>
#include <QScrollArea>
#include <QTimer>
FavoriteList::FavoriteList(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void FavoriteList::setupUI() {

    qvBoxLayout=new QVBoxLayout();//垂直布局
    QWidget *widget = new QWidget; // 创建一个小部件用于包含水平布局和按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout; // 创建水平布局用于放置按钮
    this->setStyleSheet("FavoriteList { border: 2px solid gray; border-radius: 10px; background-color: transparent; }");
    this->setContentsMargins(3, 3, 3, 3);
    refreshList =new QPushButton();
    deleteMyfPbt=new QPushButton();
    refreshList->setFont(QFont("宋体", 13));
    refreshList->setIcon(QIcon("../resource/icon/refresh.svg"));
    deleteMyfPbt->setToolTip("取消喜欢");
    deleteMyfPbt->setFont(QFont("宋体", 13));
    deleteMyfPbt->setIcon(QIcon("../resource/icon/dislike.svg"));
    refreshList->setToolTip("刷新列表");
    refreshList->setStyleSheet("QPushButton {"
                                "border: none;"
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
                               "    padding: 4px;"
                               "}"
                                "QPushButton:hover {"
                                "    background-color: #F5F5DC;"
                                "}"
                                "QPushButton:pressed {"
                                "background-color: #FFFFF0;"
                                "}");

    // 在水平布局中添加按钮
    buttonLayout->addStretch(); // 将按钮推到最右侧
    buttonLayout->addWidget(refreshList);
    buttonLayout->addSpacing(10); // 添加一些间距
    buttonLayout->addWidget(deleteMyfPbt);
    widget->setLayout(buttonLayout); // 将水平布局设置为小部件的布局

    favoriteListView=new QListView();
    favoriteListView->setFont(QFont("宋体", 13));
    favoriteListView->setStyleSheet("QListView::item { padding: 5px; }");
    // 放置在 QScrollArea 中
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(favoriteListView);
    scrollArea->setStyleSheet("  background-color: transparent;");
    qvBoxLayout->addWidget(widget);
    qvBoxLayout->addWidget(scrollArea);
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
    QTimer *timer = new QTimer(this);
    connect(deleteMyfPbt, &QPushButton::clicked, this, [=]() {
        // 设置新的图标
        deleteMyfPbt->setIcon(QIcon("../resource/icon/dislike.svg"));
        // 停止计时器（如果正在运行）并启动新的计时器
        timer->stop();
        timer->start(2500); // 设置延迟时间，单位为毫秒
    });
    connect(timer, &QTimer::timeout, this, [=]() {
        // 恢复原来的图标
        deleteMyfPbt->setIcon(QIcon("../resource/icon/like.svg"));
    });
    // 获取选中音乐的索引
    QModelIndex selectedIndex = favoriteListView->currentIndex();

// 获取音乐信息
    QString selectedMusic = selectedIndex.data(Qt::DisplayRole).toString();
//    qDebug()<<"wswdwd"<<selectedMusic<<endl;

// 从模型中删除选中的音乐
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(favoriteListView->model());
    model->removeRow(selectedIndex.row());
    favoriteList.removeAt(selectedIndex.row());
    favoriteListName.removeAt(selectedIndex.row());

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
    // 清空 favoriteList
    favoriteList.clear();
    favoriteListName.clear();
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
            QString title = parts[1];
            auto *item = new QStandardItem(title);
            qDebug()<<title<<endl;
            favoriteListName.push_back(title);
            model->appendRow(item);
        }
    }
    qDebug()<<favoriteList<<endl;
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
const QVector<QString> &FavoriteList::getFavoriteListName() const {
    return favoriteListName;
}

void FavoriteList::setFavoriteListName(const QVector<QString> &localMusicListName) {
    FavoriteList:: favoriteListName= localMusicListName;
}

FavoriteList::~FavoriteList() = default;