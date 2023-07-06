//
// Created by breezeshane on 7/5/23.
//

#ifndef PINEAPPLEMUSIC_MUSICDETAIL_H
#define PINEAPPLEMUSIC_MUSICDETAIL_H

#include <QWidget>
#include <QFile>
#include <QFrame>
#include <QMediaPlayer>
#include "playBar/PlayBar.h"
#include "model/CloudMusic.h"


QT_BEGIN_NAMESPACE
namespace Ui {
    class musicDetail;
}
QT_END_NAMESPACE

class musicDetail : public QWidget {
Q_OBJECT

public:
    explicit musicDetail(QWidget *parent = nullptr);
    explicit musicDetail(const CloudMusic& currMusic, QMediaPlayer* player,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override; // Set background pic.
    void onPositionChanged(qint64 position);

    ~musicDetail() override;

private:
    Ui::musicDetail *ui;
    PlayBar *uiBar;
    QMediaPlayer* mediaPlayer;
    QMap<int, QString> map;
};


#endif //PINEAPPLEMUSIC_MUSICDETAIL_H
