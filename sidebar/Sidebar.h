//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_SIDEBAR_H
#define PINEAPPLEMUSIC_SIDEBAR_H


#include <QWidget>
#include <QFrame>
#include <QListWidget>
#include <QVBoxLayout>
class QHBoxLayout;
class Sidebar : public QFrame {
Q_OBJECT
private:
    QVBoxLayout *mainLayout{};
    QListWidgetItem *localMusic_item{};
    QListWidgetItem *favoriteList_item{};
    QListWidgetItem *fromNet_item{};
    QListWidgetItem *chatroom_item{};
//    QListWidgetItem *playList_item{};
    QListWidget *contentLists{};


public:

    explicit Sidebar(QWidget *parent = nullptr);

    void setupUI();

    void setupContentLists();

    QListWidget *getContentLists() const;

    ~Sidebar() override;

};


#endif //PINEAPPLEMUSIC_SIDEBAR_H
