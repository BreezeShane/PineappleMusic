//
// Created by juncheng on 2023/6/27.
//

#include <QFileDialog>
#include <QTextStream>
#include <QTimer>
//#include <QDebug>
#include <QDirIterator>
#include <QJsonArray>
#include <QJsonObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QJsonDocument>
#include <QStandardItemModel>
#include <QMessageBox>
#include "LocalMusic.h"
#include <QMenu>

LocalMusic::LocalMusic(QWidget *parent)
        : QFrame(parent) {

    setupUI();

    QMenu *menu = new QMenu(musicListView);

    // 创建弹窗菜单项
    QAction *addPlay = new QAction("我喜欢", menu);
    addPlay->setIcon(QIcon("../resource/icon/like.svg"));
    menu->addAction(addPlay);

    // 设置ListView的setContextMenuPolicy属性
    musicListView->setContextMenuPolicy(Qt::CustomContextMenu);

    // 创建customContextMenuRequested信号槽
    connect(musicListView, &QListView::customContextMenuRequested, [=](const QPoint &pos) {
        // 获取右键单击的项的索引
        QModelIndex index = musicListView->indexAt(pos);
        // 如果右键单击的位置在任何项上，则显示自定义菜单
        if (index.isValid()) {
            // 在ListView上显示自定义菜单
            menu->exec(musicListView->mapToGlobal(pos));
        }
    });

    connect(addPlay, &QAction::triggered, this, &LocalMusic::addMusicToPlaylist);

}

void LocalMusic::setupUI() {
    this->setStyleSheet("LocalMusic { border: 2px solid gray; border-radius: 10px; background-color: transparent; }");
    this->setContentsMargins(3, 3, 3, 3);
    QWidget *widget = new QWidget; // 创建一个小部件用于包含水平布局和按钮
    horizontalLayout = new QHBoxLayout();// 创建水平布局用于放置按钮
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
//    horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
//
//    horizontalLayout->addItem(horizontalSpacer);

    reloadMusicPbt = new QPushButton(this);
    reloadMusicPbt->setToolTip("扫描本地音乐");
    reloadMusicPbt->setStyleSheet("QPushButton {"
//                                  "border: 2px solid gray;"
                                  "border-radius:10px;"
                                  "padding: 6px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "    background-color: #FFFFF0;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "    background-color:#FFFFF0;"
                                  "}");
    reloadMusicPbt->setEnabled(true);

    musicListView = new QListView(this);
    musicListView->setFont(QFont("宋体", 13));
    musicListView->setStyleSheet(
            "QListView { border: 2px solid gray; border-radius: 10px;background-color: transparent;padding:5px}"
            "QListView::item { padding: 5px; }");
    addMusicPlayPbt = new QPushButton();
    addMusicPlayPbt->setToolTip("添加喜欢");
    musicListView->setStyleSheet("QListView{padding:5px;background-color: transparent;}"
                                 "QListView::item{padding:5px;}"
    );
    addMusicPlayPbt = new QPushButton();
    addMusicPlayPbt->setFont(QFont("宋体", 13));

    addMusicPlayPbt->setIcon(QIcon("../resource/icon/islike.svg"));


    addMusicPlayPbt->setStyleSheet("QPushButton {"
//                                   "border: 2px solid gray;"
                                   "border-radius:10px;"
                                   "padding: 6px;"
                                   "}"
                                   "QPushButton:hover {"
                                   "    background-color:#FFFFF0;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "background-color: #FFFFF0;"
                                   "}");
    reflashpbt = new QPushButton(this);
    reflashpbt->setIcon(QIcon("../resource/icon/refresh.svg"));
    reflashpbt->setStyleSheet("QPushButton {"
                                  "border: 2px;"
                                  "border-radius:10px;"
                                  "padding: 6px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "    background-color: #FFFFF0;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "    background-color:#FFFFF0;"
                                  "}");
    // 在水平布局中添加按钮
    horizontalLayout->addStretch(); // 将按钮推到最右侧
    horizontalLayout->addWidget(reflashpbt);
    horizontalLayout->addWidget(reloadMusicPbt);
    horizontalLayout->addSpacing(10); // 添加一些间距
    horizontalLayout->addWidget(addMusicPlayPbt);


    widget->setLayout(horizontalLayout); // 将水平布局设置为小部件的布局
    verticalLayout->addWidget(widget);
    verticalLayout->addWidget(musicListView);
    // verticalLayout->addWidget(addMusicPlayPbt);
    localPlayListFile = new QFile("../resource/localMusicList.m3u");
    favoriteListFile = new QFile("../resource/favoriteListFile.m3u");

    //
    connect(reflashpbt,SIGNAL(clicked()), this, SLOT(scanLocalMusic()));
    connect(reloadMusicPbt, SIGNAL(clicked()), this, SLOT(setScanPath()));
    connect(addMusicPlayPbt, &QPushButton::clicked, this, &LocalMusic::addMusicToPlaylist);
    updateMusicList();
    retranslateUi();
}

void LocalMusic::retranslateUi() {
//    reloadMusicPbt->setText("重新扫描");
    reloadMusicPbt->setIcon(QIcon("../resource/icon/search.svg"));
}

//设置扫描路径
void LocalMusic::setScanPath() {
    // 创建一个文件对话框，让用户选择要扫描的目录
    scanPath = QFileDialog::getExistingDirectory(nullptr, "Select Directory", QDir::homePath());
    scanLocalMusic();
}

void LocalMusic::scanLocalMusic() {
    // 创建一个QMediaPlayer对象
    if (!localPlayListFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open playlist file for writing.";
        return;
    }
    addDownload();
    // 遍历目录中的所有文件
    QDir dir(scanPath);
    QStringList filters;
    filters << "*.mp3" << "*.lrc";
    dir.setNameFilters(filters);
    QFileInfoList fileList = dir.entryInfoList();
    for (const QFileInfo &fileInfo: fileList) {
        QString suffix = fileInfo.suffix();
        if (suffix == "mp3") {
            // handle mp3 file
            // 获取文件元数据
            QMediaPlayer player;
            player.setMedia(QUrl::fromLocalFile(fileInfo.filePath()));

            // 获取LRC文件名和路径
            QString lrcFileName = fileInfo.completeBaseName() + ".lrc";
            QString lrcFilePath = fileInfo.absolutePath() + "/" + lrcFileName;
            QFileInfo lrcFileInfo(lrcFilePath);

            // 获取MP3文件的长度和标题
//        QString lengthString = QString::number(player.duration() / 1000);
            QString title = player.metaData("Title").toString();
            if (title.isEmpty()) {
                title = fileInfo.fileName();
            }

            // 写入m3u文件中
            QTextStream out(localPlayListFile);
            out.setCodec("UTF-8");
//        out << "#EXTINF:" << lengthString << "," << title << "\n";
            out << "#EXTINF:" << title << "\n";
            out << fileInfo.filePath() << "\n";
            if (lrcFileInfo.exists() && lrcFileInfo.isFile()) {
                out << "lrc#" << lrcFileInfo.filePath() << "\n";
            } else {
                out << "lrc#NoLrc" << "\n";
            }
        } else if (suffix == "lrc") {
            // handle lrc file
            continue;
        } else {
            // handle other file types
            continue;
        }
    }
    localPlayListFile->close();
    updateMusicList();
}

void LocalMusic::updateMusicList() {
    localMusicList.clear();
    localMusicListLrc.clear();
    localMusicListName.clear();

    auto *model = new QStandardItemModel;
    musicListView->setModel(model);
    if (!localPlayListFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open playlist file for reading.";
        return;
    }
    QTextStream in(localPlayListFile);
    in.setCodec("UTF-8");
    QStringList titleLines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) {
            if (line.startsWith("#")) {
                titleLines << line;
            } else if (line.startsWith("lrc#")) {
                QStringList parts = line.split(QRegExp("#"));
                localMusicListLrc << parts[1];
            } else {
                localMusicList.push_back(line);
            }
        }
    }
    localPlayListFile->close();

    // 添加歌曲信息到模型中
    for (const QString &line: titleLines) {
        QStringList parts = line.split(QRegExp(":"));
        if (parts.size() == 2) {
            QString title = parts[1];
            auto *item = new QStandardItem(title);
            localMusicListName.push_back(title);
            model->appendRow(item);
        }
    }

}

void LocalMusic::addMusicToPlaylist() {
    QModelIndex index = musicListView->currentIndex();
    int row = index.row();
    QTimer *timer = new QTimer(this);
    connect(addMusicPlayPbt, &QPushButton::clicked, this, [=]() {
        // 设置新的图标
        addMusicPlayPbt->setIcon(QIcon("../resource/icon/like.svg"));
        // 停止计时器（如果正在运行）并启动新的计时器
        timer->stop();
        timer->start(2500); // 设置延迟时间，单位为毫秒
    });
    connect(timer, &QTimer::timeout, this, [=]() {
        // 恢复原来的图标
        addMusicPlayPbt->setIcon(QIcon("../resource/icon/islike.svg"));
    });
    if (row < 0) {
        qDebug() << "No music selected.";
        // 创建一个信息提示框
        QMessageBox::information(nullptr, "提示", "请选择音乐");
        return;
    }
    try {
        currentPlay = localMusicList[row];
        currentPlayLrc = localMusicListLrc[row];
        QStandardItemModel *playlistModel = new QStandardItemModel;
        QString musicName;

        if (index.isValid()) {
            musicName = index.data(Qt::DisplayRole).toString();
            playlistModel->appendRow(new QStandardItem(musicName));
        }
        //把播放文件写入musicPlayList.m3u文件
        if (!favoriteListFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qWarning() << "Failed to open playlist file for writing.";
            return;
        }

        QTextStream out(favoriteListFile);
        out.setCodec("UTF-8");
        out << "#EXTINF:" << musicName << endl;
        out << currentPlay << endl;
        out << "lrc#" << currentPlayLrc << endl;

        favoriteListFile->close();

    } catch (const std::exception &e) {
        qWarning() << "An exception occurred: " << e.what();
    }
}

//添加下载后的文件
void LocalMusic::addDownload() {
    QString download_path = "C:\\Music";
    // 遍历目录中的所有文件
    QDir dir(download_path);
    QStringList filters;
    filters << "*.mp3" << "*.lrc";
    dir.setNameFilters(filters);
    QFileInfoList fileList = dir.entryInfoList();
    for (const QFileInfo &fileInfo: fileList) {
        QString suffix = fileInfo.suffix();
        if (suffix == "mp3") {
            // handle mp3 file
            // 获取文件元数据
            QMediaPlayer player;
            player.setMedia(QUrl::fromLocalFile(fileInfo.filePath()));

            // 获取LRC文件名和路径
            QString lrcFileName = fileInfo.completeBaseName() + ".lrc";
            QString lrcFilePath = fileInfo.absolutePath() + "/" + lrcFileName;
            QFileInfo lrcFileInfo(lrcFilePath);

            // 获取MP3文件的长度和标题
//        QString lengthString = QString::number(player.duration() / 1000);
            QString title = player.metaData("Title").toString();
            if (title.isEmpty()) {
                title = fileInfo.fileName();
            }

            // 写入m3u文件中
            QTextStream out(localPlayListFile);
            out.setCodec("UTF-8");
//        out << "#EXTINF:" << lengthString << "," << title << "\n";
            out << "#EXTINF:" << title << "\n";
            out << fileInfo.filePath() << "\n";
            if (lrcFileInfo.exists() && lrcFileInfo.isFile()) {
                out << "lrc#" << lrcFileInfo.filePath() << "\n";
            } else {
                out << "lrc#NoLrc" << "\n";
            }
        } else if (suffix == "lrc") {
            // handle lrc file
            continue;
        } else {
            // handle other file types
            continue;
        }
    }
    //localPlayListFile->close();
}


QListView *LocalMusic::getMusicListView() const {
    return musicListView;
}

const QVector<QString> &LocalMusic::getPlayList() const {
    return localMusicList;
}

const QVector<QString> &LocalMusic::getPlayListLrc() const {
    return localMusicListLrc;
}

const QVector<QString> &LocalMusic::getLocalMusicListName() const {
    return localMusicListName;
}

void LocalMusic::setLocalMusicListName(const QVector<QString> &localMusicListName) {
    LocalMusic::localMusicListName = localMusicListName;
}



void LocalMusic::reflash_mushic() {

}


LocalMusic::~LocalMusic() = default;