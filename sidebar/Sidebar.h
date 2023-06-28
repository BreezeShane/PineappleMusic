//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_SIDEBAR_H
#define PINEAPPLEMUSIC_SIDEBAR_H


#include <QWidget>
#include <QFrame>
#include <QListWidget>
class QHBoxLayout;
class Sidebar : public QFrame {
Q_OBJECT
private:
    QHBoxLayout *mainLayout{};
    QListWidgetItem *page1Button{};
    QListWidgetItem *page2Button{};
    QListWidget *contentLists{};

public:

    explicit Sidebar(QWidget *parent = nullptr);

    void setupUI();

    void setupContentLists();

    QListWidget *getContentLists() const;

    ~Sidebar() override;

};


#endif //PINEAPPLEMUSIC_SIDEBAR_H
