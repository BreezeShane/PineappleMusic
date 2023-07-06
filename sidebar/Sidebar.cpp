//
// Created by juncheng on 2023/6/27.
//

#include <QHBoxLayout>
#include <QPushButton>
#include "Sidebar.h"

Sidebar::Sidebar(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void Sidebar::setupUI() {
    this->setStyleSheet("border: 2px solid gray;border-radius:10px;padding:10px;");
    this->setFixedWidth(200);

    mainLayout = new QVBoxLayout;

    QWidget *logo1 = new QWidget;
    logo1->setFixedHeight(150);
    //logo1->setStyleSheet("border-image: url(../resource/icon/logo.png);background-size: stretch;");
    mainLayout->addWidget(logo1);

    setupContentLists();

    mainLayout->addWidget(contentLists);
    mainLayout->setContentsMargins(0,0,0,0);    //取出外边距
    this->setLayout(mainLayout);
}

void Sidebar::setupContentLists() {
    contentLists = new QListWidget;
    contentLists->setSpacing(10);
    contentLists->setCurrentRow(0);
    contentLists->setFont(QFont("宋体", 15));
    contentLists->setStyleSheet("border: 2px solid gray;border-radius:10px;padding:5px;background-color: transparent;");

    favoriteList_item = new QListWidgetItem(contentLists);
    favoriteList_item->setText(tr("我喜欢"));
    favoriteList_item->setIcon(QIcon("../resource/icon/like.svg"));
    favoriteList_item->setTextAlignment(Qt::AlignHCenter);
    favoriteList_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    localMusic_item = new QListWidgetItem(contentLists);  //设置显示列表
    localMusic_item->setText(tr("本地音乐"));
    localMusic_item->setIcon(QIcon("../resource/icon/musicLocal.svg"));
    localMusic_item->setBackground(QColor(0,0,0,0));
    localMusic_item->setTextAlignment(Qt::AlignHCenter);
    localMusic_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    fromNet_item = new QListWidgetItem(contentLists);
    fromNet_item->setText(tr("网络探索"));
    fromNet_item->setIcon(QIcon("../resource/icon/netMusic.svg"));
    fromNet_item->setTextAlignment(Qt::AlignHCenter);
    fromNet_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    chatroom_item = new QListWidgetItem(contentLists);
    chatroom_item->setText(tr("音乐交流"));
    chatroom_item->setIcon(QIcon("../resource/icon/message.svg"));
    chatroom_item->setTextAlignment(Qt::AlignHCenter);
    chatroom_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    playList_item = new QListWidgetItem(contentLists);
    playList_item->setText(tr("播放列表"));
    playList_item->setIcon(QIcon("../resource/icon/message.svg"));
    playList_item->setTextAlignment(Qt::AlignHCenter);
    playList_item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

QListWidget *Sidebar::getContentLists() const {
    return contentLists;
}

Sidebar::~Sidebar() = default;
