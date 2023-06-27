//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_TOPBAR_H
#define PINEAPPLEMUSIC_TOPBAR_H


#include <QFrame>

class TopBar : public QFrame
{
    Q_OBJECT
public:
    explicit TopBar(QWidget *parent = nullptr);
    void setupUI();
    ~TopBar() override;
};


#endif //PINEAPPLEMUSIC_TOPBAR_H
