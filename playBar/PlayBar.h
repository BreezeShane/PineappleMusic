//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_PLAYBAR_H
#define PINEAPPLEMUSIC_PLAYBAR_H


#include <QFrame>

class PlayBar : public QFrame
{
    Q_OBJECT
public:
    explicit PlayBar(QWidget *parent = nullptr);
    void setupUI();

    ~PlayBar() override;
};


#endif //PINEAPPLEMUSIC_PLAYBAR_H
