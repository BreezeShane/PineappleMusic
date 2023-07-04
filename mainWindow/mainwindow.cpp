#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <iostream>
#include <QTime>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMessageBox>
#include "mainwindow.h"
#include "sidebar/Sidebar.h"
#include "mainContent/MainContent.h"
#include "playBar/PlayBar.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

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

}

// 槽函数，用于切换播放模式
void MainWindow::togglePlayMode() {
    switch (currentPlayMode) {
        case SingleLoop:
            currentPlayMode = Sequential;
            playBar->getPbtModel()->setText("顺序播放");
            //ui->playModeButton->setIcon(QIcon(":/icons/sequential.png"));
            break;
        case Sequential:
            currentPlayMode = Random;
            playBar->getPbtModel()->setText("随机播放");
            //ui->playModeButton->setIcon(QIcon(":/icons/random.png"));
            break;
        case Random:
            currentPlayMode = SingleLoop;
            playBar->getPbtModel()->setText("单曲循环");
            //ui->playModeButton->setIcon(QIcon(":/icons/loop_single.png"));
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

    // 子布局中加入两个部件
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
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(onPositionChanged(qint64)));
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(onDurationChanged(qint64)));
    connect(playBar->getSlider(),SIGNAL(valueChanged(int)),this,SLOT(slot_valueChanged_progress(int)));
    connect(playBar->getSlider(), SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));

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
        


    });
    connect(playBar->getSlider(), SIGNAL(sliderPressed()), this, SLOT(onSliderPressed()));
}

void MainWindow::retranslateUi() {
    //标题
    this->setWindowTitle("Pineapple Music");
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


MainWindow::~MainWindow() = default;

