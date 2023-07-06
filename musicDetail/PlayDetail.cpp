//
// Created by juncheng on 2023/7/6.
//

#include "PlayDetail.h"
#include <QDebug>
void PlayDetail::setupUI() {
    //标题
    this->setWindowTitle("歌词详情");
    this->setWindowIcon(QIcon("../resource/icon/music.svg"));
    this->setStyleSheet("border-radius: 10px;");
    this->setMinimumSize(1200, 800);
    mainLayout = new QVBoxLayout;

    lrcLabel = new LyricWidget;
    lrcLabel->setLyricFile(music->getLrcPath());

    QObject::connect(mediaPlayer, &QMediaPlayer::positionChanged, [=](qint64 position) {
        displayLyrics();
    });
    playBar = new PlayBar(mediaPlayer);
    mainLayout->addWidget(lrcLabel);
    mainLayout->addWidget(playBar);
    // 设置背景图的样式
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(QPixmap("../resource/image/17.jpg")));
    this->setPalette(palette);
    this->setLayout(mainLayout);
}

PlayDetail::PlayDetail(CloudMusic *music, QMediaPlayer* mediaPlayer, QWidget *parent) {
    this->mediaPlayer=mediaPlayer;
    this->setMusic(music);
    setupUI();
}

const QMetaObject &PlayDetail::getStaticMetaObject() {
    return staticMetaObject;
}

LyricWidget *PlayDetail::getLrcLabel() const {
    return lrcLabel;
}

void PlayDetail::setLrcLabel(LyricWidget *lrcLabel) {
    PlayDetail::lrcLabel = lrcLabel;
}

CloudMusic *PlayDetail::getMusic() const {
    return music;
}

void PlayDetail::setMusic(CloudMusic *music) {
    PlayDetail::music = music;
}

PlayBar *PlayDetail::getPlayBar() const {
    return playBar;
}

void PlayDetail::setPlayBar(PlayBar *playBar) {
    PlayDetail::playBar = playBar;
}

QMediaPlayer *PlayDetail::getMediaPlayer() const {
    return mediaPlayer;
}

void PlayDetail::setMediaPlayer(QMediaPlayer *mediaPlayer) {
    PlayDetail::mediaPlayer = mediaPlayer;
}

QVBoxLayout *PlayDetail::getMainLayout() const {
    return mainLayout;
}

void PlayDetail::setMainLayout(QVBoxLayout *mainLayout) {
    PlayDetail::mainLayout = mainLayout;
}

void PlayDetail::displayLyrics() {
    lrcLabel->setCurrentTime(mediaPlayer->position());
}

PlayDetail::~PlayDetail() = default;
