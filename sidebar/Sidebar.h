//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_SIDEBAR_H
#define PINEAPPLEMUSIC_SIDEBAR_H


#include <QWidget>
#include <QFrame>

class Sidebar : public QFrame
{
    Q_OBJECT
public:
    explicit Sidebar(QWidget *parent = nullptr);
    void setupUI();
    ~Sidebar() override;
};


#endif //PINEAPPLEMUSIC_SIDEBAR_H
