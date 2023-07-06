//
// Created by juncheng on 2023/7/6.
//

#ifndef PINEAPPLEMUSIC_PLAYDETAIL_H
#define PINEAPPLEMUSIC_PLAYDETAIL_H


#include <QFrame>
#include <QVBoxLayout>
#include "model/CloudMusic.h"
#include "playBar/PlayBar.h"
#include "LyricWidget.h"
#include <QMediaPlayer>

class PlayDetail : public QFrame {
Q_OBJECT

public:
    explicit PlayDetail(CloudMusic *music, QMediaPlayer *mediaPlayer, QWidget *parent = nullptr);

    static const QMetaObject &getStaticMetaObject();

    LyricWidget *getLrcLabel() const;

    void setLrcLabel(LyricWidget *lrcLabel);

    CloudMusic *getMusic() const;

    void setMusic(CloudMusic *music);

    PlayBar *getPlayBar() const;

    void setPlayBar(PlayBar *playBar);

    QMediaPlayer *getMediaPlayer() const;

    void setMediaPlayer(QMediaPlayer *mediaPlayer);

    QVBoxLayout *getMainLayout() const;

    void setMainLayout(QVBoxLayout *mainLayout);

    ~PlayDetail() override;
public slots:
    void displayLyrics();
private:
    void setupUI();

    LyricWidget *lrcLabel{};
    CloudMusic* music{};
    PlayBar *playBar{};
    QMediaPlayer *mediaPlayer{};
    QVBoxLayout *mainLayout{};
};


#endif //PINEAPPLEMUSIC_PLAYDETAIL_H
