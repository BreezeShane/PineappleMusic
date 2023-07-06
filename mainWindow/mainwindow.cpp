#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <iostream>
#include <QTime>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include "mainwindow.h"
#include "sidebar/Sidebar.h"
#include "mainContent/MainContent.h"
#include "playBar/PlayBar.h"
#include "musicDetail/musicDetail.h"
#include <QGraphicsEffect>
#include <QGraphicsOpacityEffect>
#include "favoriteList/FavoriteList.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setupUI();
    lyricsUi();
    playBar->getSlider()->installEventFilter(this);
    connect(sidebar->getContentLists(),  //将显示列表与堆栈窗口关联，点击列表中的按键，显示相应的窗口
            SIGNAL(currentItemChanged(QListWidgetItem * , QListWidgetItem * )),
            this, SLOT(changePage(QListWidgetItem * , QListWidgetItem * )));

    QObject::connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            qDebug() << "Media playback has ended.";
            nextMusic();
        }
    });
    // 播放模式切换按键
    QObject::connect(playBar->getPbtModel(), SIGNAL(clicked()), this, SLOT(togglePlayMode()));

    QObject::connect(playBar->getPbtLyrics(), SIGNAL(clicked()),
                     this,
                     SLOT(lyricsModel()));

    QObject::connect(playBar->getPbtLyrics(), SIGNAL(clicked()),
                     this,
                     SLOT(creatLyricsWindow()));

    QObject::connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, [=](qint64 position) {
        lyrics.clear();
        timestamps.clear();
        labelRight->clear();
        labelLeft->clear();
        getLyrics(currentPlayLrc);
    });

    QObject::connect(mediaPlayer, &QMediaPlayer::positionChanged, [=](qint64 position) {
        displayLyrics();
    });
}

void MainWindow::lyricsUi() {

    widget = new QWidget;
    layoutV = new QVBoxLayout(); // 创建垂直布局
    layoutB_1 = new QHBoxLayout(); // 创建水平布局
    layoutB_2 = new QHBoxLayout(); // 创建水平布局
    labelLeft = new QLabel("");
    labelRight = new QLabel("");

    widget->setGeometry(500, 700, 1000, 150);
    widget->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
    widget->setWindowOpacity(0.5);
    widget->setWindowTitle("Lyrics");

    QFont font("Arial", 29, QFont::Bold);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::darkBlue);
    labelLeft->setPalette(palette);
    labelLeft->setFont(font);
    labelRight->setFont(font);
    labelRight->setPalette(palette);

    layoutB_1->addWidget(labelLeft);
    layoutB_1->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    layoutB_2->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layoutB_2->addWidget(labelRight);

    layoutV->addLayout(layoutB_1);
    layoutV->addLayout(layoutB_2);

    widget->setLayout(layoutV);
}

void MainWindow::creatLyricsWindow() {
    if (currenLyricsModel == yes) {
        widget->show();
    } else {
        widget->hide();
    }
}

void MainWindow::lyricsModel() {
    switch (currenLyricsModel) {
        case yes:
            playBar->getPbtLyrics()->setIcon(QIcon("../resource/icon/lyricsOff.svg"));
            currenLyricsModel = no;
            break;
        case no:
            playBar->getPbtLyrics()->setIcon(QIcon("../resource/icon/lyricsOn.svg"));
            currenLyricsModel = yes;
            break;
    }
}

// 槽函数，用于切换播放模式
void MainWindow::togglePlayMode() {
    switch (currentPlayMode) {
        case SingleLoop:
            currentPlayMode = Sequential;
            playBar->getPbtModel()->setIcon(QIcon("../resource/icon/sequence.svg"));
            break;
        case Sequential:
            currentPlayMode = Random;
            playBar->getPbtModel()->setIcon(QIcon("../resource/icon/random.svg"));
            break;
        case Random:
            currentPlayMode = SingleLoop;
            playBar->getPbtModel()->setIcon(QIcon("../resource/icon/onlyone.svg"));
            break;
    }
}
//设置侧边栏点击
void MainWindow::changePage(QListWidgetItem *current, QListWidgetItem *previous) {
    if (!current)
        current = previous;
    QString currentText = current->text();
   // qDebug()<<currentText;
    if (currentText == "播放列表") {
        // 执行特定操作
        int currentIndex = sidebar->getContentLists()->row(current);
        mainContent->getContentPages()->setCurrentIndex(currentIndex);
//        openPlayListC();
    } else {
        // 切换到其他页面
        int currentIndex = sidebar->getContentLists()->row(current);
        mainContent->getContentPages()->setCurrentIndex(currentIndex);
    }
}

void MainWindow::setupUI() {
    //主窗口最小大小
    this->setMinimumSize(1200, 800);

    // 获取屏幕的宽度和高度
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    // 计算QWidget的位置，使其居中显示
    int x = (screenWidth - this->width()) / 2;
    int y = (screenHeight - this->height()) / 2 - 50;
    this->move(x, y);

    //主部件
    auto centralwidget = new QWidget(this);

    // 从持久化设置中读取背景图路径，默认为默认背景图
    QString imagePath = QSettings().value("BackgroundImage", "../resource/image/4.jpg").toString();
    // 设置背景图的样式
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QPixmap(imagePath)));
    this->setPalette(palette);
//    // 创建颜色调整效果
    QGraphicsEffect *effect = new QGraphicsOpacityEffect(this);
    effect->setEnabled("");

    // 创建一个QWidget作为中央部件
    centralwidget->setMinimumSize(1200, 800);
    centralwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(centralwidget);

    // 主布局---水平布局
    mainLayout = new QHBoxLayout();
    // 子布局---垂直布局
    subLayout = new QVBoxLayout();
    // 侧边栏
    sidebar = new Sidebar();
    // 内容显示区域
    mainContent = new MainContent();
    // 播放控制栏
    playBar = new PlayBar();
    //工具栏
    toolbar = new QToolBar();
    toolLayout = new QHBoxLayout();

    personalizebt = new QPushButton();
    helpbt = new QPushButton();
    personalizebt->setIcon(QIcon("../resource/icon/skin.svg"));
    helpbt->setToolTip("帮助文档");
    helpbt->setIcon(QIcon("../resource/icon/help.svg"));
    // 设置个性化按钮的样式
    personalizebt->setFont(QFont("宋体", 8));
    personalizebt->setStyleSheet("QPushButton {"
                                 "    border: 2px;"
                                 "border-radius:10px;"
                                 "    padding: 6px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "    background-color: #FFFFF0;"
                                 "}"
                                 "QPushButton:pressed {"
                                 "    background-color:#FFFFF0;"
                                 "}");
    personalizebt->setToolTip("个性化");
    helpbt->setStyleSheet("QPushButton {"
                          "    border: 2px;"
                          "border-radius:10px;"
                          "    padding: 6px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #FFFFF0;"
                          "}"
                          "QPushButton:pressed {"
                          "    background-color:#FFFFF0;"
                          "}");

    // 添加伸缩器到工具栏，将按钮推到最右边
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolbar->addWidget(spacer);
    toolbar->addWidget(personalizebt);
    toolbar->addWidget(helpbt);
    toolLayout->addWidget(toolbar);
    // 子布局中加入两个部件
    subLayout->addLayout(toolLayout);
    subLayout->addWidget(mainContent);
    subLayout->addWidget(playBar);

    // 主布局中加入侧边栏和子布局
    mainLayout->addWidget(sidebar);
    mainLayout->addLayout(subLayout);

    // 主部件加载主布局
    centralwidget->setLayout(mainLayout);

    //实例化播放器
    mediaPlayer = new QMediaPlayer;
    //播放列表实例化
    playList = new CurrentPlayList;
    //侧边栏播放列表实例化
    playListC = new PlayList;

    retranslateUi();
    //开始 - 暂停
    connect(playBar->getPbtStartOrPause(),
            SIGNAL(clicked()),
            this,
            SLOT(startOrPauseMusic()));
    //前一首
    connect(playBar->getPbtPrevious(),
            SIGNAL(clicked()),
            this,
            SLOT(previousMusic()));
    //后一首
    connect(playBar->getPbtNext(),
            SIGNAL(clicked()),
            this,
            SLOT(nextMusic()));
    //本地音乐列表点击事件
    connect(mainContent->getLocalMusicPage()->getMusicListView(), &QListView::clicked, [&](const QModelIndex &index) {
        // 获取所选项的QMediaPlayer对象，并播放音乐
        int row = index.row();
        if (row >= 0 && row < mainContent->getLocalMusicPage()->getPlayList().size()) {
            currentPlaylist = mainContent->getLocalMusicPage()->getPlayList();
            currentPlaylistName = mainContent->getLocalMusicPage()->getLocalMusicListName();
            currentPlaylistLrc = mainContent->getLocalMusicPage()->getPlayListLrc();
            currentPlayName = currentPlaylistName[row];
            currentPlay = currentPlaylist[row];
            currentPlayLrc = currentPlaylistLrc[row];
            mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
            mediaPlayer->play();

            playBar->setMusicName(currentPlayName);
            playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/stopp.svg"));
            playBar->getSlider()->setSliderPosition(0);
        }
    });
    //我喜欢列表点击事件
    connect(mainContent->getFavoriteListPage()->getFavoriteListView(), &QListView::clicked,
            [&](const QModelIndex &index) {
                // 获取所选项的QMediaPlayer对象，并播放音乐
                int row = index.row();
                qDebug() << index.row();
                if (row >= 0 && row < mainContent->getFavoriteListPage()->getFavoriteList().size()) {
                    currentPlaylist = mainContent->getFavoriteListPage()->getFavoriteList();
                    currentPlaylistName = mainContent->getFavoriteListPage()->getFavoriteListName();
                    currentPlaylistLrc = mainContent->getFavoriteListPage()->getFavoriteListLrc();
                    currentPlay = currentPlaylist[row];
                    currentPlayName = currentPlaylistName[row];
                    currentPlayLrc = currentPlaylistLrc[row];
                    mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
                    mediaPlayer->play();

                    playBar->setMusicName(currentPlayName);
                    playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/stopp.svg"));
                    playBar->getSlider()->setSliderPosition(0);
                }
            });

    connect(mainContent->getFromNetPage()->resultListView, &QListView::clicked, this, [=](const QModelIndex &index) {
        // 获取用户点击的项的数据
        int songId = index.data(Qt::UserRole).toInt();
        music.setArtist(index.data(Qt::UserRole + 1).toString());
        music.setAlbumUrl(index.data(Qt::UserRole + 2).toString());
        music.setDuration(index.data(Qt::UserRole + 3).toInt());
        music.setName(index.data(Qt::UserRole + 4).toString());
        auto *manager = new QNetworkAccessManager(this);
        QString url = "https://service-qbrcywo4-1314545420.gz.apigw.tencentcs.com/release/song/url";
        QUrlQuery query;
        query.addQueryItem("id", QString::number(songId));
        url.append("?" + query.toString());
        QNetworkRequest request(url);

        QNetworkReply *reply = manager->get(request);

        connect(reply, &QNetworkReply::finished, this, [=]() {
            QString url{};
            if (reply->error() == QNetworkReply::NoError) {
                QString response = reply->readAll();
                const QString &jsonStr = response;  // 从服务器获取的 JSON 数据
                QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
                if (!doc.isNull()) {
                    QJsonObject obj = doc.object();
                    if (obj.contains("data")) {
                        QJsonArray data = obj["data"].toArray();
                        if (!data.isEmpty()) {
                            QJsonObject item = data[0].toObject();
                            if (item.contains("url")) {
                                url = item["url"].toString();
                                music.setMusicUrl(url);
                            }
                        }
                    }
                }
                // 处理响应数据
            } else {
                qDebug() << "error";
                // 处理错误
            }
            reply->deleteLater();

        });

        // 在这里处理用户点击事件，例如显示该歌曲的详细信息
        QUrl url2(music.getAlbumUrl());
        QNetworkRequest request2(url2);
        qDebug() << url2;
        QNetworkReply *reply2 = manager->get(request2);
        //显示专辑图
        connect(reply2, &QNetworkReply::finished, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray data2 = reply2->readAll();
                QPixmap pixmap2;
                pixmap2.loadFromData(data2);
                // 将pixmap显示在UI上
                playBar->setAlbum(pixmap2);
            } else {
                // 处理错误情况
                qWarning() << "can not load album" << url;
            }
        });
        playBar->setMusicName(music.getName());
        currentPlaylist.clear();
        currentPlaylist.append(music.getName());
        currentPlaylistLrc.clear();
        currentPlaylistLrc.append("NoLrc");
        currentPlay = music.getMusicUrl();
        currentPlayLrc = "NoLrc";
        QUrl url1(currentPlay);
        mediaPlayer->setMedia(url1);
        mediaPlayer->play();
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/stopp.svg"));
        playBar->getSlider()->setSliderPosition(0);
    });
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(onDurationChanged(qint64)));
    connect(playBar->getSlider(), SIGNAL(valueChanged(int)), this, SLOT(slot_valueChanged_progress(int)));
    connect(playBar->getSlider(), SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));

    connect(playBar->getSlider(), SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
    connect(playBar->getAction1(), SIGNAL(triggered()), this, SLOT(setPlaySpeed()));
    connect(playBar->getAction2(), SIGNAL(triggered()), this, SLOT(setPlaySpeed()));
    connect(playBar->getAction3(), SIGNAL(triggered()), this, SLOT(setPlaySpeed()));
    connect(playBar->getAction4(), SIGNAL(triggered()), this, SLOT(setPlaySpeed()));
    //跳转播放详情页
    connect(playBar->getAlbum(), SIGNAL(clicked()), this, SLOT(openDetailWindow()));
    // 换肤连接
    connect(personalizebt, &QPushButton::clicked, this, &MainWindow::changeBackground);
    //打开帮助文档
    connect(helpbt, &QPushButton::clicked, this, &MainWindow::helpShow);
    //打开播放列表
    connect(playBar->getPbtPlayList(), &QPushButton::clicked, this, &MainWindow::openPlayList);
    //打开侧边栏播放列表

    //播放列表点击事件
    connect(playList->getPlayListView(), &QListView::clicked, [&](const QModelIndex &index) {
        // 获取所选项的QMediaPlayer对象，并播放音乐
        int row = index.row();
        // qDebug() << index.row();
        if (row >= 0 && row < playList->getCurrentPlaylist().size()) {
            currentPlaylist = playList->getCurrentPlaylist();
            currentPlaylistName = playList->getCurrentPlaylistName();
            currentPlaylistLrc = playList->getCurrentPlaylistLrc();
            currentPlay = currentPlaylist[row];
            currentPlayName = currentPlaylistName[row];
            currentPlayLrc = currentPlaylistLrc[row];
            mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
            mediaPlayer->play();

            playBar->setMusicName(currentPlayName);
            playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/stopp.svg"));
            playBar->getSlider()->setSliderPosition(0);
        }
    });
    //url播放
    connect(mainContent->getFromNetPage()->getFindButton(),&QPushButton::clicked,[=](){
        qDebug()<<"播放"<<endl;
        QString url_text = mainContent->getFromNetPage()->geturl_in()->text();
        if(url_text == NULL){
            QMessageBox::information(this,"提示","请输入url");
            return ;
        }
        QUrl url(url_text);
        mediaPlayer->setMedia(url);
        mediaPlayer->play();
        currentPlay = url_text;
        playBar->setMusicName("unkown");
    });

}

void MainWindow::openPlayListC() {
    // qDebug()<<currentPlaylistName<<"播放列表";
    playListC->setCurrentPlaylistName(currentPlaylistName);
    playListC->setCurrentPlaylist(currentPlaylist);
    playListC->setCurrentPlay(currentPlay);
    playListC->setCurrentPlaylistLrc(currentPlaylistLrc);
    playListC->setCurrentPlayLrc(currentPlayLrc);
    playListC->setCurrentPlayName(currentPlayName);
    playListC->show_list();
}

void MainWindow::openPlayList() {

    if (playList->isHidden()) {
        playList->setCurrentPlaylistName(currentPlaylistName);
        playList->setCurrentPlaylist(currentPlaylist);
        playList->setCurrentPlay(currentPlay);
        playList->setCurrentPlaylistLrc(currentPlaylistLrc);
        playList->setCurrentPlayLrc(currentPlayLrc);
        playList->setCurrentPlayName(currentPlayName);
        playList->show();
    } else {
        playList->hide();
    }
}

void MainWindow::retranslateUi() {
    //标题
    this->setWindowTitle("Pineapple Music");
    this->setWindowIcon(QIcon("../resource/icon/app.png"));
}

//帮助文档
void MainWindow::helpShow() {
    QMessageBox::about(this, u8"关于", " Pineapple Music| 一款精致小巧的本地音乐播放器\n"
                                       "【歌词文件说明】需要与对应歌曲MP3在同目录且同名（.lry文件）\n"
                                       "【使用说明】\n"
                                       " Pineapple Music音乐播放器暂未设置快捷键使用\n"
                                       " 上一曲/下一曲/暂停/播放  点击播放栏的相应图标即可\n"
                                       " 顺序播放/随机播放/循环播放 点击播放栏的相应图标即可\n"
                                       " 播放速度 可设置0.5/1/1.5/2倍数播放音乐\n"
                                       "【添加本地音乐】点击本地音乐界面的扫描添加按钮\n"
                                       "【查看歌曲歌词】点击播放栏界面的专辑图片\n"
                                       "【音乐文件类型】添加过程中会自动过滤得到可播放的文件类型（.mp3/.flac/.mpga文件），所以添加时无需考虑文件类型，使用\"Ctrl+A\"选择文件夹内全部文件添加即可\n"
                                       "\n注：鼠标移动到不认识的按钮上，会有说明哦~\n");
}

//个性化
void MainWindow::changeBackground() {

    // 打开文件选择对话框，选择图片文件
    QString imagePath = QFileDialog::getOpenFileName(this, "选择图片", QDir::homePath(),
                                                     "Images (*.png *.jpg *.jpeg *.svg)");
    //qDebug() << "换肤" << endl;
    // 如果用户选择了图片文件
    if (!imagePath.isEmpty()) {
        // 设置新的背景图路径
//centralWidget()->setStyleSheet(QString("QWidget { background-image: url(%1); }").arg(imagePath));
        QPalette palette;
        palette.setBrush(this->backgroundRole(), QBrush(QPixmap(imagePath)));
        this->setPalette(palette);
        // 将背景图路径存储到持久化设置中
        QSettings().setValue("BackgroundImage", imagePath);
    } else {
        // 如果用户取消选择图片，则将背景图路径从持久化设置中删除
        QSettings().remove("BackgroundImage");
    }

}

void MainWindow::startOrPauseMusic() {
    if (mediaPlayer != nullptr && mediaPlayer->state() == QMediaPlayer::PlayingState) {
        mediaPlayer->pause();
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/play.svg"));
    } else {
        mediaPlayer->play();
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/stopp.svg"));
    }
}

void MainWindow::previousMusic() {
    switch (currentPlayMode) {
        case SingleLoop:
            // 如果启用了单曲循环，则上一首歌曲是当前歌曲
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (int it = 0; it <= currentPlaylist.size() - 1; it++) {
                    if (currentPlaylist[it] == currentPlay) {
                        currentPlay = currentPlaylist[it];
                        currentPlayLrc = currentPlaylistLrc[it];
                        currentPlayName = currentPlaylistName[it];
                        break;
                    }
                }
            }
            break;
        case Sequential:
            // 否则，获取上一首歌曲的索引
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (int it = 0; it <= currentPlaylist.size() - 1; it++) {
                    if (currentPlay == currentPlaylist[0]) {
                        currentPlay = currentPlaylist[currentPlaylist.size() - 1];
                        currentPlayLrc = currentPlaylistLrc[currentPlaylistLrc.size() - 1];
                        currentPlayName = currentPlaylistName[currentPlaylistName.size() - 1];
                        break;
                    } /*else if(currentPlay == currentPlaylist[size()]){
                        currentPlay = *(currentPlaylist.end()-2);
                        break;
                    }*/else if (currentPlaylist[it] == currentPlay) {
                        currentPlay = currentPlaylist[it - 1];
                        currentPlayLrc = currentPlaylistLrc[it - 1];
                        currentPlayName = currentPlaylistName[it - 1];
                        break;
                    }
                }
            }
            break;
        case Random:
            // 创建一个随机数生成器
            std::srand(std::time(nullptr));
            auto random_number = std::rand();
            qDebug() << random_number;
            // 如果是随机播放，则获取一个随机索引
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (int it = 0; it <= currentPlaylist.size() - 1; ++it) {
                    if (currentPlaylist[it] == currentPlay) {
                        currentPlay = currentPlaylist[random_number % currentPlaylist.size()];
                        currentPlayLrc = currentPlaylistLrc[random_number % currentPlaylistLrc.size()];
                        currentPlayName = currentPlaylistName[random_number % currentPlaylistName.size()];
                        break;
                    }
                }
            }
            break;
    }
    mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
    mediaPlayer->play();
    playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/stopp.svg"));
    playBar->setMusicName(currentPlayName);
}

void MainWindow::nextMusic() {
//    getLyrics(currentPlayLrc);
    switch (currentPlayMode) {
        case SingleLoop:
            // 如果启用了单曲循环，则下一首歌曲是当前歌曲
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (int it = 0; it <= currentPlaylist.size() - 1; it++) {
                    if (currentPlaylist[it] == currentPlay) {
                        currentPlay = currentPlaylist[it];
                        currentPlayLrc = currentPlaylistLrc[it];
                        currentPlayName = currentPlaylistName[it];
                        break;
                    }
                }
            }
            break;
        case Sequential:
            // 否则，获取下一首歌曲的索引
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (int it = 0; it <= currentPlaylist.size() - 1; it++) {
                    if (currentPlay == currentPlaylist[currentPlaylist.size() - 1]) {
                        currentPlay = currentPlaylist[0];
                        currentPlayLrc = currentPlaylistLrc[0];
                        currentPlayName = currentPlaylistName[0];
                        break;
                    } else if (currentPlaylist[it] == currentPlay) {
                        currentPlay = currentPlaylist[it + 1];
                        currentPlayLrc = currentPlaylistLrc[it + 1];
                        currentPlayName = currentPlaylistName[it + 1];
                        break;
                    }
                }
            }
            break;
        case Random:
            // 创建一个随机数生成器
            std::srand(std::time(nullptr));
            auto random_number = std::rand();
            qDebug() << random_number;
            // 如果是随机播放，则获取一个随机索引
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (int it = 0; it <= currentPlaylist.size() - 1; ++it) {
                    if (currentPlaylist[it] == currentPlay) {
                        currentPlay = currentPlaylist[random_number % currentPlaylist.size()];
                        currentPlayLrc = currentPlaylistLrc[random_number % currentPlaylistLrc.size()];
                        currentPlayName = currentPlaylistName[random_number % currentPlaylistLrc.size()];
                        break;
                    }
                }
            }
            break;
    }
    mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
    mediaPlayer->play();
    playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/stopp.svg"));
    playBar->setMusicName(currentPlayName);
}

//进度条滑块数值改变槽函数
void MainWindow::slot_valueChanged_progress(int value) {
    if (qAbs(mediaPlayer->position() - value) > 99)//不加会出现卡顿
        mediaPlayer->setPosition(value);    //设置播放器的当前进度
}

//当前媒体总时长改变槽函数
void MainWindow::onDurationChanged(qint64 duration) {
    playBar->getSlider()->setMaximum(duration); //设置进度条最大值 也就是歌曲时长 ms
    int secs = duration / 1000; //全部秒数
    int mins = secs / 60;//分
    secs = secs % 60;//秒
    durationTime = QString::asprintf("%02d:%02d", mins, secs);
    playBar->getCurrentProcess()->setText(positionTime);
    playBar->getFinalProcess()->setText(durationTime);
}

//当前进度改变槽函数
void MainWindow::onPositionChanged(qint64 position) {
    if (playBar->getSlider()->isSliderDown())
        return;//如果手动调整进度条，则不处理
    playBar->getSlider()->setSliderPosition(position);
    updateCurrentProcessText();
}

void MainWindow::onSliderPressed() {
    updateCurrentProcessText();
    mediaPlayer->setPosition(
            playBar->getSlider()->value() * mediaPlayer->duration() / playBar->getSlider()->maximum()); // 设置播放器的当前进度
}

void MainWindow::updateCurrentProcessText() {
    if (mediaPlayer != nullptr) {
        qint64 position = mediaPlayer->position();
        int secs = position / 1000;
        int mins = secs / 60;
        secs = secs % 60;
        positionTime = QString::asprintf("%02d:%02d", mins, secs);
        playBar->getCurrentProcess()->setText(positionTime);
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == playBar->getSlider() && event->type() == QEvent::MouseMove) {
        updateCurrentProcessText();
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::setPlaySpeed() {
    QObject *senderObj = sender(); // 获取信号发送者对象指针

    if (senderObj == playBar->getAction1()) {
        currentSpeed = 0.5;
        playBar->getSpeedMenu()->setTitle("0.5x");
    } else if (senderObj == playBar->getAction2()) {
        currentSpeed = 1.0;
        playBar->getSpeedMenu()->setTitle("1.0x");
    } else if (senderObj == playBar->getAction3()) {
        currentSpeed = 1.5;
        playBar->getSpeedMenu()->setTitle("1.5x");
    } else if (senderObj == playBar->getAction4()) {
        currentSpeed = 2.0;
        playBar->getSpeedMenu()->setTitle("2.0x");
    }
    mediaPlayer->setPlaybackRate(currentSpeed);
}

//展示播放详情页
void MainWindow::openDetailWindow() {
    music.setName(currentPlayName);
    music.setMusicUrl(currentPlay);
    music.setDuration(durationTime.toInt());
    music.setPositionTime(positionTime);
    music.setLrcPath(currentPlayLrc);

    if (detailWindow == nullptr) {
//        detailWindow = new musicDetail(music);
        detailWindow = new musicDetail(music, mediaPlayer);
//        detailWindow = new PlayDetail(&music,mediaPlayer);
        detailWindow->show();
    } else {
        if (detailWindow->isHidden()) {
            detailWindow->show();
        } else {
            detailWindow->hide();
        }
    }
//    win->setMusic(music);
}

//获取歌词
void MainWindow::getLyrics(const QString& filepath){
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("[") && line.contains("]")) {
            int pos = line.indexOf("]");
            QString timestampStr = line.mid(1, pos - 1);
            QString lyricsStr = line.mid(pos + 1).trimmed();
            QTime timestamp = QTime::fromString(timestampStr, "mm:ss.z");
            if (!timestamp.isValid()) {
                qDebug() << "Invalid timestamp: " << timestampStr;
                continue;
            }
            int timestampMs = timestamp.minute() * 60 * 1000 + timestamp.second() * 1000 + timestamp.msec();
            timestamps.append(timestampMs);
            lyrics.append(lyricsStr);
        }
    }
}

void MainWindow::displayLyrics() {
    int currentTime = mediaPlayer->position(); // 获取当前播放时间
    // 查找当前应该显示哪一句歌词
    int currentIndex = -1;

    for (int i = 0; i <= timestamps.size()-1; i = i+1) {
        if (timestamps[i] > currentTime+1000) {
            break;
        }
        currentIndex = i;
    }
    // 更新歌词显示
    if (currentIndex >= 0 && currentIndex % 2 == 0 && currentIndex <= lyrics.size()) {
        labelLeft->setText(lyrics[currentIndex]);
    } else if (currentIndex >= 0 && currentIndex % 2 != 0 && currentIndex <= lyrics.size() ){
        labelRight->setText(lyrics[currentIndex]);
    }
}

MainWindow::~MainWindow() = default;

