//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_PLAYLIST_H
#define PINEAPPLEMUSIC_PLAYLIST_H

#include <QFrame>

class PlayList : public QFrame
{
Q_OBJECT
public:
    explicit PlayList(QWidget *parent = nullptr);
    void setupUI();

    ~PlayList() override;
};


#endif //PINEAPPLEMUSIC_PLAYLIST_H
