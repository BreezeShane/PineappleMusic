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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    lyricsUi();

    setupUI();
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
    QObject::connect(playBar->getPbtModel(), SIGNAL(clicked()),this,SLOT(togglePlayMode()));

    QObject::connect(playBar->getPbtLyrics(), SIGNAL(clicked()),
                     this,
                     SLOT(lyricsModel()));

    QObject::connect(playBar->getPbtLyrics(), SIGNAL(clicked()),
                     this,
                     SLOT(creatLyricsWindow()));

}

void MainWindow::lyricsUi(){

    widget = new QWidget;
    QVBoxLayout *layoutV = new QVBoxLayout(); // 创建垂直布局
    QHBoxLayout *layoutB_1 = new QHBoxLayout(); // 创建水平布局
    QHBoxLayout *layoutB_2 = new QHBoxLayout(); // 创建水平布局
    QLabel *labelLeft = new QLabel("llll");
    QLabel *labelRight = new QLabel("rrrr");

    widget->setGeometry(500, 700, 1000, 150);
    widget->setWindowFlags(Qt::FramelessWindowHint);
    widget->setWindowOpacity(1);

    layoutB_1->addWidget(labelLeft);
    layoutB_1->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    layoutB_2->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layoutB_2->addWidget(labelRight);

    layoutV->addLayout(layoutB_1);
    layoutV->addLayout(layoutB_2);

    widget->setLayout(layoutV);
}

void MainWindow::creatLyricsWindow(){

    if(currenLyricsModel == yes){
        widget->show();
    }else{
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
            //playBar->getPbtModel()->setText("顺序播放");
            playBar->getPbtModel()->setIcon(QIcon("../resource/icon/sequential.svg"));
            break;
        case Sequential:
            currentPlayMode = Random;
            //playBar->getPbtModel()->setText("随机播放");
            playBar->getPbtModel()->setIcon(QIcon("../resource/icon/random.svg"));
            break;
        case Random:
            currentPlayMode = SingleLoop;
            //playBar->getPbtModel()->setText("单曲循环");
            playBar->getPbtModel()->setIcon(QIcon("../resource/icon/singleloop.svg"));
            break;
    }
}

void MainWindow::changePage(QListWidgetItem *current, QListWidgetItem *previous) const {
    if (!current)
        current = previous;
    mainContent->getContentPages()->setCurrentIndex(sidebar->getContentLists()->row(current));
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
    QString imagePath = QSettings().value("BackgroundImage", "../resource/image/1.jpg").toString();
    // 设置背景图的样式
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(QPixmap(imagePath)));
    this->setPalette(palette);
//    // 创建颜色调整效果
    QGraphicsEffect* effect = new QGraphicsOpacityEffect(this);
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
    toolbar=new QToolBar();
    toolLayout=new QHBoxLayout();

    personalizebt=new QPushButton();
    helpbt=new QPushButton();
    personalizebt->setIcon(QIcon("../resource/icon/skin.svg"));
    helpbt->setIcon(QIcon("../resource/icon/help.svg"));
    // 设置个性化按钮的样式
    personalizebt->setFont(QFont("宋体", 8));
    personalizebt->setStyleSheet("QPushButton {"
                                     "    border: 2px;"
                                     "border-radius:10px;"
                                     "    padding: 6px;"
                                     "}"
                                     "QPushButton:hover {"
                                     "    background-color: #ADD8E6;"
                                     "}"
                                     "QPushButton:pressed {"
                                     "    background-color:#ADD8E6 ;"
                                     "}");
    helpbt->setStyleSheet("QPushButton {"
                                 "    border: 2px;"
                                 "border-radius:10px;"
                                 "    padding: 6px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "    background-color: #ADD8E6;"
                                 "}"
                                 "QPushButton:pressed {"
                                 "    background-color:#ADD8E6 ;"
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
    connect(mainContent->getLocalMusicPage()->getMusicListView(), &QListView::clicked, [&](const QModelIndex &index) {
        // 获取所选项的QMediaPlayer对象，并播放音乐
        int row = index.row();
        if (row >= 0 && row < mainContent->getLocalMusicPage()->getPlayList().size()) {
            currentPlaylist = mainContent->getLocalMusicPage()->getPlayList();
            currentPlaylistLrc = mainContent->getLocalMusicPage()->getPlayListLrc();
            currentPlay = currentPlaylist[row];
            currentPlayLrc = currentPlaylistLrc[row];
            mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
            mediaPlayer->play();
            playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/pause.png"));
            playBar->getSlider()->setSliderPosition(0);
        }
    });
    connect(mainContent->getFromNetPage()->resultListView, &QListView::clicked, this, [=](const QModelIndex& index) {
        // 获取用户点击的项的数据
        int songId = index.data(Qt::UserRole).toInt();
        music.setArtist(index.data(Qt::UserRole+1).toString());
        music.setAlbumUrl(index.data(Qt::UserRole+2).toString());
        music.setDuration(index.data(Qt::UserRole+3).toInt());
        music.setName(index.data(Qt::UserRole+4).toString());
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
        qDebug()<<url2;
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
                qWarning()<<"can not load album"<<url;
            }
        });
        currentPlaylist.clear();
        currentPlaylist.append(music.getName());
        currentPlaylistLrc.clear();
        currentPlaylistLrc.append("NoLrc");
        currentPlay = music.getMusicUrl();
        currentPlayLrc ="NoLrc";
        QUrl url1(currentPlay);
        mediaPlayer->setMedia(url1);
        mediaPlayer->play();
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/pause.png"));
        playBar->getSlider()->setSliderPosition(0);
    });
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(onPositionChanged(qint64)));
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(onDurationChanged(qint64)));
    connect(playBar->getSlider(),SIGNAL(valueChanged(int)),this,SLOT(slot_valueChanged_progress(int)));
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
}

void MainWindow::retranslateUi() {
    //标题
    this->setWindowTitle("Pineapple Music");
    this->setWindowIcon(QIcon("../resource/app.png"));
}
void MainWindow::helpShow() {
    QMessageBox::information(this, "帮助文档", "这里是帮助文档的内容");
}
void MainWindow::changeBackground() {

    // 打开文件选择对话框，选择图片文件
    QString imagePath = QFileDialog::getOpenFileName(this, "选择图片", QDir::homePath(), "Images (*.png *.jpg *.jpeg *.svg)");
    qDebug()<<"换肤"<<endl;
    // 如果用户选择了图片文件
    if (!imagePath.isEmpty()) {
        // 设置新的背景图路径
//        centralWidget()->setStyleSheet(QString("QWidget { background-image: url(%1); }").arg(imagePath));
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
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/start.png"));
    } else {
        mediaPlayer->play();
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/pause.png"));
    }
}


void MainWindow::previousMusic() {
    switch (currentPlayMode) {
        case SingleLoop:
            // 如果启用了单曲循环，则上一首歌曲是当前歌曲
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end() - 1; it++) {
                    if (*it == currentPlay) {
                        currentPlay = *(it);
                        break;
                    }
                }
            }
            break;
        case Sequential:
            // 否则，获取上一首歌曲的索引
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end() - 1; it++) {
                    if(currentPlay == *currentPlaylist.begin()) {
                        currentPlay = *(currentPlaylist.end()-1);
                        break;
                    } else if(currentPlay == *(currentPlaylist.end()-1)){
                        currentPlay = *(currentPlaylist.end()-2);
                        break;
                    }else if (*it == currentPlay) {
                        currentPlay = *(it - 1);
                        break;
                    }
                }
            }
            break;
        case Random:
            // 创建一个随机数生成器
            std::srand(std::time(nullptr));
            auto random_number = std::rand();
            qDebug()<< random_number;
            // 如果是随机播放，则获取一个随机索引
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end() - 1; ++it) {
                    for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end() - 1; it++) {
                        if (*it == currentPlay) {
                            currentPlay = currentPlaylist[random_number%currentPlaylist.size()];
                            break;
                        }
                    }
                }
            }
            break;
    }
    mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
    mediaPlayer->play();
    playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/pause.png"));
}

void MainWindow::nextMusic() {
    switch (currentPlayMode) {
        case SingleLoop:
            // 如果启用了单曲循环，则下一首歌曲是当前歌曲
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end() - 1; it++) {
                    if (*it == currentPlay) {
                        currentPlay = *(it);
                        break;
                    }
                }
            }
            break;
        case Sequential:
            // 否则，获取下一首歌曲的索引
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end() - 1; it++) {
                    if(currentPlay == *(currentPlaylist.end()-1)) {
                        currentPlay = *currentPlaylist.begin();
                        break;
                    } else if (*it == currentPlay) {
                        currentPlay = *(it + 1);
                        break;
                    }
                }
            }
            break;
        case Random:
            // 创建一个随机数生成器
            std::srand(std::time(nullptr));
            auto random_number = std::rand();
            qDebug()<< random_number;
            // 如果是随机播放，则获取一个随机索引
            if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
                mediaPlayer->stop();
                for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end() - 1; ++it) {
                    for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end() - 1; it++) {
                        if (*it == currentPlay) {
                            currentPlay = currentPlaylist[random_number%currentPlaylist.size()];
                            break;
                        }
                    }
                }

            }
            break;
    }
    mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
    mediaPlayer->play();
    playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/pause.png"));
}

//进度条滑块数值改变槽函数
void MainWindow::slot_valueChanged_progress(int value)
{
    if(qAbs (mediaPlayer->position() - value ) > 99)//不加会出现卡顿
        mediaPlayer->setPosition(value);    //设置播放器的当前进度
}

//当前媒体总时长改变槽函数
void MainWindow::onDurationChanged(qint64 duration)
{
    playBar->getSlider()->setMaximum(duration); //设置进度条最大值 也就是歌曲时长 ms
    int secs = duration/1000; //全部秒数
    int mins = secs/60;//分
    secs = secs % 60;//秒
    durationTime = QString::asprintf("%02d:%02d",mins,secs);
    playBar->getCurrentProcess()->setText(positionTime);
    playBar->getFinalProcess()->setText(durationTime);
}

//当前进度改变槽函数
void MainWindow::onPositionChanged(qint64 position)
{
    if(playBar->getSlider()->isSliderDown())
        return;//如果手动调整进度条，则不处理
    playBar->getSlider()->setSliderPosition(position);
    updateCurrentProcessText();
}

void MainWindow::onSliderPressed() {
    updateCurrentProcessText();
    mediaPlayer->setPosition(playBar->getSlider()->value()*mediaPlayer->duration()/playBar->getSlider()->maximum()); // 设置播放器的当前进度
}
void MainWindow::updateCurrentProcessText()
{
    if (mediaPlayer != nullptr) {
        qint64 position = mediaPlayer->position();
        int secs = position / 1000;
        int mins = secs / 60;
        secs = secs % 60;
        positionTime = QString::asprintf("%02d:%02d", mins, secs);
        playBar->getCurrentProcess()->setText(positionTime);
    }
}
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == playBar->getSlider() && event->type() == QEvent::MouseMove) {
        updateCurrentProcessText();
    }
    return QMainWindow::eventFilter(obj, event);
}

//void MainWindow::setPlaySpeed(){
//    if (playBar->getSpeedMenu()->title() == "0.5x") {
//        currentSpeed = 0.5;
//    } else if (playBar->getSpeedMenu()->title() == "1.0x") {
//        currentSpeed = 1.0;
//    } else if (playBar->getSpeedMenu()->title() == "1.5x") {
//        currentSpeed = 1.5;
//    } else if (playBar->getSpeedMenu()->title() == "2.0x") {
//        currentSpeed = 2.0;
//    }
//    mediaPlayer->setPlaybackRate(currentSpeed);
//}
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
    musicDetail* win = new musicDetail(music);
//    win->setMusic(music);
    win->show();
}

MainWindow::~MainWindow() = default;

