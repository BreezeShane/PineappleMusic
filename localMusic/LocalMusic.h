//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_LOCALMUSIC_H
#define PINEAPPLEMUSIC_LOCALMUSIC_H


#include <QFrame>

class LocalMusic : public QFrame
{
Q_OBJECT
public:
    explicit LocalMusic(QWidget *parent = nullptr);
    void setupUI();

    ~LocalMusic() override;
};



#endif //PINEAPPLEMUSIC_LOCALMUSIC_H
