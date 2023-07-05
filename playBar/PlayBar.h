//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_PLAYBAR_H
#define PINEAPPLEMUSIC_PLAYBAR_H


#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QSlider>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include "qSlider/MySlider.h"

class PlayBar : public QFrame {
Q_OBJECT
private:
    QHBoxLayout *qhBoxLayout{};
    QPushButton *album{};    //专辑图片
    QPushButton *pbtModel{};  //播放模式按钮
    QPushButton *pbtLyrics{};
public:
    QPushButton *getPbtLyrics() const;

private:
    QPushButton *pbtPrevious{};
    QPushButton *pbtStartOrPause{};
    QPushButton *pbtNext{};
    QLabel *currentProcess{};
    QLabel *finalProcess{};
    QMenuBar *speedMenuBar{};
    QMenu *speedMenu{};
    QAction *action1{};//倍速
    QAction *action2{};
    QAction *action3{};
    QAction *action4{};
    QVBoxLayout *playCentralQv{};
    QHBoxLayout *playCentralQh{};
    MySlider *sliderProcess{};
    QLabel *music_name{};
public:
    explicit PlayBar(QWidget *parent = nullptr);

    void setupUI();

    void retranslateUi();

    QPushButton *getAlbum() const;

    void setAlbum(const QPixmap &music_album);

    QPushButton *getPbtPrevious() const;

    QPushButton *getPbtStartOrPause() const;

    QPushButton *getPbtNext() const;

    QPushButton *getPbtModel() const;

    MySlider *getSlider() const;

    QLabel *getCurrentProcess() const;

    QLabel *getFinalProcess() const;

    QMenu *getSpeedMenu() const;

    QAction *getAction1() const;

    QAction *getAction2() const;

    QAction *getAction3() const;

    QAction *getAction4() const;

    QLabel *getMusicName() const;

    void setMusicName(QString musicName);

    ~PlayBar() override;

    static const QMetaObject &getStaticMetaObject();
};

#endif //PINEAPPLEMUSIC_PLAYBAR_H
