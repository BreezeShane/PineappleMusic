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
    contentLists->setStyleSheet("QListWidget { border: none; }");

    page1Button = new QListWidgetItem(contentLists);  //设置显示列表
    page1Button->setText(tr("本地音乐"));
    page1Button->setTextAlignment(Qt::AlignHCenter);
    page1Button->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    page2Button = new QListWidgetItem(contentLists);
    page2Button->setText(tr("播放列表"));
    page2Button->setTextAlignment(Qt::AlignHCenter);
    page2Button->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

}

QListWidget *Sidebar::getContentLists() const {
    return contentLists;
}

Sidebar::~Sidebar() = default;
