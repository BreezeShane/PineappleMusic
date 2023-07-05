//
// Created by 伊蕾娜 on 2023/7/3.
//

#ifndef PINEAPPLEMUSIC_MYSLIDER_H
#define PINEAPPLEMUSIC_MYSLIDER_H
#include <QSlider>
#include <QWidget>
class MySlider : public QSlider
{
Q_OBJECT
public:
    MySlider(Qt::Orientation orientation,QWidget *parent = nullptr);
    ~MySlider();

protected:
    void mousePressEvent(QMouseEvent *event);  //单击
};

#endif //PINEAPPLEMUSIC_MYSLIDER_H
