//
// Created by juncheng on 2023/6/27.
//

#include "LocalMusic.h"

LocalMusic::LocalMusic(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void LocalMusic::setupUI() {
    this->setStyleSheet("border: 2px solid gray;border-radius:10px;");
    this->setContentsMargins(3, 3, 3, 3);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    horizontalLayout = new QHBoxLayout();
    horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    reloadMusicPbt = new QPushButton(this);
    reloadMusicPbt->setStyleSheet("padding:5px;");
    reloadMusicPbt->setEnabled(true);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(reloadMusicPbt->sizePolicy().hasHeightForWidth());
    reloadMusicPbt->setSizePolicy(sizePolicy);
    reloadMusicPbt->setLayoutDirection(Qt::LeftToRight);

    horizontalLayout->addWidget(reloadMusicPbt);


    verticalLayout->addLayout(horizontalLayout);

    musicListView = new QListView(this);
//    musicListView->setStyleSheet("margin:5px;padding:5px;");
    verticalLayout->addWidget(musicListView);
    retranslateUi();
}

void LocalMusic::retranslateUi() {
    reloadMusicPbt->setText("重新加载");
    reloadMusicPbt->setIcon(QIcon("../resource/icon/search.svg"));
} // retranslateUi

LocalMusic::~LocalMusic() = default;