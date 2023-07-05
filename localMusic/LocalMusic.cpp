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
#include <QMessageBox>
#include "LocalMusic.h"

LocalMusic::LocalMusic(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void LocalMusic::setupUI() {
    this->setStyleSheet("border: 2px solid gray;border-radius:10px;background-color: transparent;");
    this->setContentsMargins(3, 3, 3, 3);

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    horizontalLayout = new QHBoxLayout();
    horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    reloadMusicPbt = new QPushButton(this);
    reloadMusicPbt->setStyleSheet("QPushButton {"
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
    addMusicPlayPbt=new QPushButton("我喜欢");
    addMusicPlayPbt->setFont(QFont("宋体", 13));
    addMusicPlayPbt->setStyleSheet("QPushButton {"
                                   "border: 2px solid gray;"
                                   "border-radius:10px;"
                                   "padding: 6px;"
                                   "}"
                                   "QPushButton:hover {"
                                   "    background-color:#FFFFF0;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "background-color: #FFFFF0;"
                                   "}");

    verticalLayout->addWidget(musicListView);
    verticalLayout->addWidget(addMusicPlayPbt);
    localPlayListFile = new QFile("../resource/localMusicList.m3u");
    favoriteListFile=new QFile("../resource/favoriteListFile.m3u");

    connect(reloadMusicPbt, SIGNAL(clicked()), this, SLOT(scanLocalMusic()));
    connect(addMusicPlayPbt, &QPushButton::clicked, this, &LocalMusic::addMusicToPlaylist);
    updateMusicList();
    retranslateUi();
}

void LocalMusic::retranslateUi() {
//    reloadMusicPbt->setText("重新扫描");
    reloadMusicPbt->setIcon(QIcon("../resource/icon/search.svg"));
} // retranslateUi

void LocalMusic::scanLocalMusic() {
    // 创建一个QMediaPlayer对象
    // 创建一个文件对话框，让用户选择要扫描的目录
    QString scanPath = QFileDialog::getExistingDirectory(nullptr, "Select Directory", QDir::homePath());

    if (!localPlayListFile->open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open playlist file for writing.";
        return;
    }

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

    // 添加歌曲信息到模型中
    for (const QString &line: titleLines) {
        QStringList parts = line.split(QRegExp(":"));
        if (parts.size() == 2) {
//            QString artist = parts[0];
//            QString title = parts[1];
            QString title = parts[1];
            auto *item = new QStandardItem(title);
            localMusicListName.push_back(title);
            model->appendRow(item);
        }
    }
    localPlayListFile->close();
}
void LocalMusic::addMusicToPlaylist() {
    QModelIndex index = musicListView->currentIndex();
    int row = index.row();

    if (row < 0) {
        qDebug() << "No music selected.";
        // 创建一个信息提示框
        QMessageBox::information(nullptr, "提示", "请选择音乐");
        return;
    }

    try {
        currentPlay = localMusicList[row];
        QStandardItemModel *playlistModel = new QStandardItemModel;
        QString musicName;

        if (index.isValid())
        {
            musicName = index.data(Qt::DisplayRole).toString();
            qDebug() << "jjj" << index.data(Qt::DisplayRole).toString() << endl;
            playlistModel->appendRow(new QStandardItem(musicName));
        }

        //把播放文件写入musicPlayList.m3u文件
        if (!favoriteListFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qWarning() << "Failed to open playlist file for writing.";
            return;
        }

        QTextStream out(favoriteListFile);

//        out << "#EXTINF:" << musicName << endl;
//        out << currentPlay << endl;
        out.setCodec("UTF-8");
        out << "#EXTINF:" << musicName << endl;
        out << currentPlay << endl;


        favoriteListFile->close();
    } catch (const std::exception& e) {
        qWarning() << "An exception occurred: " << e.what();
    }
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


LocalMusic::~LocalMusic() = default;