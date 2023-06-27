//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_RECENTLIST_H
#define PINEAPPLEMUSIC_RECENTLIST_H

#include <QFrame>

class RecentList : public QFrame
{
Q_OBJECT
public:
    explicit RecentList(QWidget *parent = nullptr);
    void setupUI();

    ~RecentList() override;
};


#endif //PINEAPPLEMUSIC_RECENTLIST_H
