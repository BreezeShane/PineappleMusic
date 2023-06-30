#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <iostream>
#include "mainwindow.h"
#include "sidebar/Sidebar.h"
#include "mainContent/MainContent.h"
#include "playBar/PlayBar.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setupUI();

    connect(sidebar->getContentLists(),  //将显示列表与堆栈窗口关联，点击列表中的按键，显示相应的窗口
            SIGNAL(currentItemChanged(QListWidgetItem * , QListWidgetItem * )),
            this, SLOT(changePage(QListWidgetItem * , QListWidgetItem * )));
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
        if (mediaPlayer != nullptr && mediaPlayer->state() == QMediaPlayer::PlayingState) {
            mediaPlayer->stop();
        }
        int row = index.row();
        if (row >= 0 && row < mainContent->getLocalMusicPage()->getPlayList().size()) {
            currentPlaylist = mainContent->getLocalMusicPage()->getPlayList();
            currentPlay = currentPlaylist[row];
            mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
            mediaPlayer->play();
            playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/pause.png"));
        }
    });
}

void MainWindow::retranslateUi() {
    //标题
    this->setWindowTitle("Pineapple Music");
}

QMediaPlayer *MainWindow::getMediaPlayer() const {
    return mediaPlayer;
}

const QVector<QString> &MainWindow::getCurrentPlaylist() const {
    return currentPlaylist;
}

void MainWindow::setCurrentPlaylist(const QVector<QString> &playlist) {
    MainWindow::currentPlaylist = playlist;
}

void MainWindow::startOrPauseMusic() {
    if (mediaPlayer != nullptr && mediaPlayer->state() == QMediaPlayer::PlayingState) {
        mediaPlayer->stop();
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/start.png"));
    } else {
        mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
        mediaPlayer->play();
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/pause.png"));
    }
}

const QString &MainWindow::getCurrentPlay() const {
    return currentPlay;
}

void MainWindow::setCurrentPlay(const QString &musicPath) {
    MainWindow::currentPlay = musicPath;
}

void MainWindow::previousMusic() {
    if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
        mediaPlayer->stop();
        for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end(); it++) {
            if (*it == currentPlay && it != currentPlaylist.begin()) {
                currentPlay = *(it-1);
                break;
            }
        }
        mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
        mediaPlayer->play();
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/pause.png"));
    }
}

void MainWindow::nextMusic() {
    if (!currentPlaylist.empty() && !currentPlay.isEmpty()) {
        mediaPlayer->stop();
        for (QVector<QString>::iterator it = currentPlaylist.begin(); it != currentPlaylist.end() - 1; it++) {
            if (*it == currentPlay) {
                currentPlay = *(it+1);
                break;
            }
        }
        mediaPlayer->setMedia(QUrl::fromLocalFile(currentPlay));
        mediaPlayer->play();
        playBar->getPbtStartOrPause()->setIcon(QIcon("../resource/icon/pause.png"));
    }
}


MainWindow::~MainWindow() = default;

