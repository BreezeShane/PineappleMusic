//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_SIDEBAR_H
#define PINEAPPLEMUSIC_SIDEBAR_H


#include <QWidget>
#include <QFrame>
#include <QListWidget>

class Sidebar : public QFrame
{
    Q_OBJECT


public:
    QListWidget *contentLists{};

    explicit Sidebar(QWidget *parent = nullptr);
    void setupUI();
    void setupContentLists();
    ~Sidebar() override;


};


#endif //PINEAPPLEMUSIC_SIDEBAR_H
