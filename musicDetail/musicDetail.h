//
// Created by breezeshane on 7/5/23.
//

#ifndef PINEAPPLEMUSIC_MUSICDETAIL_H
#define PINEAPPLEMUSIC_MUSICDETAIL_H

#include <QWidget>
#include <QFile>
#include "playBar/PlayBar.h"
#include "model/CloudMusic.h"


QT_BEGIN_NAMESPACE
namespace Ui {
    class musicDetail;
//    class DetailedPagePlayBar;
}
QT_END_NAMESPACE

//class DetailedPagePlayBar : public ::PlayBar {
//public:
//    explicit DetailedPagePlayBar(QWidget *parent = nullptr);
//};

class musicDetail : public QWidget {
Q_OBJECT

public:
    explicit musicDetail(QWidget *parent = nullptr);
    explicit musicDetail(CloudMusic currMusic,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override; // Set background pic.

    ~musicDetail() override;

private:
    Ui::musicDetail *ui;
    ::PlayBar *uiBar;
};


#endif //PINEAPPLEMUSIC_MUSICDETAIL_H
