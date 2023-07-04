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
#include "qSlider/MySlider.h"
class PlayBar : public QFrame
{
    Q_OBJECT
private:
    QHBoxLayout * qhBoxLayout{};
    QSpacerItem *horizontalSpacer{};
    QPushButton *pbtPrevious{};
    QPushButton *pbtStartOrPause{};
    QPushButton *pbtNext{};
    MySlider *sliderProcess{};
    QLabel *currentProcess{};
    QLabel *finalProcess{};
public:
    explicit PlayBar(QWidget *parent = nullptr);
    void setupUI();
    void retranslateUi();

    QPushButton *getPbtPrevious() const;

    QPushButton *getPbtStartOrPause() const;

    QPushButton *getPbtNext() const;

    MySlider *getSlider() const;

    QLabel * getCurrentProcess() const;

    QLabel * getFinalProcess() const;

    ~PlayBar() override;

    static const QMetaObject &getStaticMetaObject();
};

#endif //PINEAPPLEMUSIC_PLAYBAR_H
