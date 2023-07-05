//
// Created by juncheng on 2023/6/27.
//

#include "PlayBar.h"

PlayBar::PlayBar(QWidget *parent) : QFrame(parent) {

    setupUI();
}

void PlayBar::setupUI() {
    this->setStyleSheet("QWidget { border: 2px solid gray; border-radius: 10px; background-color: transparent; }");
    this->setFixedHeight(100);
    qhBoxLayout = new QHBoxLayout(this);
    album = new QPushButton();
    album->setFixedSize(80, 80);
    album->setIconSize(QSize(80, 80));
    pbtLyrics = new QPushButton();
    pbtModel = new QPushButton();
    pbtPrevious = new QPushButton();
    pbtStartOrPause = new QPushButton();
    pbtNext = new QPushButton();

    playCentralQv = new QVBoxLayout;
    playCentralQh = new QHBoxLayout;
    music_name = new QLabel("music name");
    music_name->setStyleSheet("QLabel { border: none; padding-left: 10px; }");
    speedMenuBar = new QMenuBar();
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    speedMenuBar->setSizePolicy(sizePolicy);
    currentProcess = new QLabel();
    finalProcess = new QLabel();
    sliderProcess = new MySlider(Qt::Horizontal, this);

    currentProcess->setText("00:00");
    finalProcess->setText("00:00");
    currentProcess->setFixedSize(50, 50);//设置大小
    finalProcess->setFixedSize(50, 50);
    currentProcess->setStyleSheet("QLabel {"
                                  "background-color: transparent;"
                                  //"border: 1px solid gray;"
                                  "border: none;" //隐藏边框
                                  "border-radius: 4px;"
                                  "padding: 2px;"
                                  "}");

    finalProcess->setStyleSheet("QLabel {"
                                "background-color: transparent;"
//                                "border: 1px solid gray;"
                                "border: none;"
                                "border-radius: 4px;"
                                "padding: 2px;"
                                "}");

    sliderProcess->setStyleSheet("QSlider::groove:horizontal {"    //修改进度条样式
                               "border: none;"
                                 "height: 8px;"
                                "border-radius: 0px;"
                                 "background: lightgray;"
                                 "}"
                                 "QSlider::handle:horizontal {"
                                 "background: rgb(255, 120, 0);"
                                 "border: none;"
                                 "width: 16px;"
                                 "height: 16px;"
                                 "margin: -5px 0;"
                                 "border-radius: 8px;"
                                 "}"
                                 "QSlider::sub-page:horizontal {"
                                 "height: 4px;"
                                 "border-radius: 3px;"
                                 "background: rgb(255, 170, 0);"
                                 "}"
                                 "QSlider::add-page:horizontal {"
                                 "height: 4px;"
                                 "border-radius: 3px;"
                                 "background: lightgray;"
                                 "}");


    speedMenu = new QMenu(speedMenuBar);
    speedMenuBar->addAction(speedMenu->menuAction());
    speedMenu->setTitle(tr("1.0x"));
    //QMenu *playMenu = speedMenu->addMenu("1.0x");

    action1 = new QAction(this);
    action2 = new QAction(this);
    action3 = new QAction(this);
    action4 = new QAction(this);

    speedMenu->addAction(action1);
    speedMenu->addSeparator();//给菜单加分隔条
    speedMenu->addAction(action2);
    speedMenu->addSeparator();
    speedMenu->addAction(action3);
    speedMenu->addSeparator();
    speedMenu->addAction(action4);
    action1->setText("0.5x");
    action2->setText("1.0x");
    action3->setText("1.5x");
    action4->setText("2.0x");

    qhBoxLayout->addWidget(album);

    playCentralQv->addWidget(music_name);
    playCentralQh->addWidget(currentProcess);
    playCentralQh->addWidget(sliderProcess);
    playCentralQh->addWidget(finalProcess);
    playCentralQv->addLayout(playCentralQh);
    qhBoxLayout->addLayout(playCentralQv);

    qhBoxLayout->addWidget(pbtLyrics);
    qhBoxLayout->addWidget(pbtModel);
    qhBoxLayout->addWidget(pbtPrevious);
    qhBoxLayout->addWidget(pbtStartOrPause);
    qhBoxLayout->addWidget(pbtNext);

    this->setLayout(qhBoxLayout);
    retranslateUi();
}

void PlayBar::retranslateUi() {
    QPixmap pixmap("../resource/icon/app.png");
    QSize size(60, 60);
    QPixmap scaledPixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::FastTransformation);
    album->setIcon(scaledPixmap);
    pbtLyrics->setIcon(QIcon("../resource/icon/lyricsOff.svg"));
    pbtModel->setIcon(QIcon("../resource/icon/sequence.svg"));

    pbtPrevious->setIcon(QIcon("../resource/icon/up.svg"));
    pbtPrevious->setIconSize(QSize(50, 50));
    pbtStartOrPause->setIcon(QIcon("../resource/icon/play.svg"));
    pbtStartOrPause->setIconSize(QSize(50, 50));
    pbtNext->setIcon(QIcon("../resource/icon/later.svg"));
    pbtNext->setIconSize(QSize(50, 50));

}

QPushButton *PlayBar::getPbtPrevious() const {
    return pbtPrevious;
}

QPushButton *PlayBar::getPbtStartOrPause() const {
    return pbtStartOrPause;
}

QPushButton *PlayBar::getPbtNext() const {
    return pbtNext;
}

MySlider *PlayBar::getSlider() const {
    return sliderProcess;
}

QLabel *PlayBar::getCurrentProcess() const {
    return currentProcess;
}

QLabel *PlayBar::getFinalProcess() const {
    return finalProcess;
}

QPushButton *PlayBar::getPbtModel() const {
    return pbtModel;
}

QPushButton *PlayBar::getPbtLyrics() const {
    return pbtLyrics;
}

QMenu *PlayBar::getSpeedMenu() const {
    return speedMenu;
}

QAction *PlayBar::getAction1() const {
    return action1;
}

QAction *PlayBar::getAction2() const {
    return action2;
}

QAction *PlayBar::getAction3() const {
    return action3;
}

QAction *PlayBar::getAction4() const {
    return action4;
}

QPushButton *PlayBar::getAlbum() const {
    return album;
}

void PlayBar::setAlbum(const QPixmap &music_album) {
    PlayBar::album->setIcon(music_album);
}

QLabel *PlayBar::getMusicName() const {
    return music_name;
}

void PlayBar::setMusicName(QString musicName) {
    music_name->setText(musicName);
}

PlayBar::~PlayBar() = default;