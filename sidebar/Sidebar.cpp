//
// Created by juncheng on 2023/6/27.
//

#include <QHBoxLayout>
#include "Sidebar.h"

Sidebar::Sidebar(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void Sidebar::setupUI() {
    this->setStyleSheet("border: 2px solid gray;border-radius:10px;padding:10px;");
    this->setFixedWidth(200);
    setupContentLists();
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(contentLists);
    mainLayout->setContentsMargins(0,0,0,0);    //取出外边距
    this->setLayout(mainLayout);
}

void Sidebar::setupContentLists() {
    contentLists = new QListWidget;
    contentLists->setCurrentRow(0);
    contentLists->setFont(QFont("宋体", 15));
    contentLists->setStyleSheet("border: 2px solid gray;border-radius:10px;padding:5px;");

    localMusic_item = new QListWidgetItem(contentLists);  //设置显示列表
    localMusic_item->setText(tr("本地音乐"));
    localMusic_item->setTextAlignment(Qt::AlignHCenter);
    localMusic_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    playList_item = new QListWidgetItem(contentLists);
    playList_item->setText(tr("播放列表"));
    playList_item->setTextAlignment(Qt::AlignHCenter);
    playList_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    fromNet_item = new QListWidgetItem(contentLists);
    fromNet_item->setText(tr("网络播放"));
    fromNet_item->setTextAlignment(Qt::AlignHCenter);
    fromNet_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    chatroom_item = new QListWidgetItem(contentLists);
    chatroom_item->setText(tr("聊天室"));
    chatroom_item->setTextAlignment(Qt::AlignHCenter);
    chatroom_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

QListWidget *Sidebar::getContentLists() const {
    return contentLists;
}

Sidebar::~Sidebar() = default;
