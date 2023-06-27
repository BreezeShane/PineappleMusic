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
    this->setStyleSheet("border-radius: 10px;background-color: red;");
    this->setFixedWidth(200);
    setupContentLists();
    auto *layout = new QHBoxLayout;
    layout->addWidget(contentLists);
    this->setLayout(layout);
}

void Sidebar::setupContentLists() {
    contentLists = new QListWidget;
    contentLists->setCurrentRow(0);
    auto *page1Button = new QListWidgetItem(contentLists);  //设置显示列表
    page1Button->setText(tr("本地音乐"));
    page1Button->setTextAlignment(Qt::AlignHCenter);
    page1Button->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    auto *page2Button = new QListWidgetItem(contentLists);
    page2Button->setText(tr("最近播放"));
    page2Button->setTextAlignment(Qt::AlignHCenter);
    page2Button->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

}

Sidebar::~Sidebar() = default;
