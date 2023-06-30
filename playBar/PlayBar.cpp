//
// Created by juncheng on 2023/6/27.
//

#include "PlayBar.h"

PlayBar::PlayBar(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void PlayBar::setupUI() {
    this->setStyleSheet("border: 2px solid gray;border-radius:10px;");
    this->setFixedHeight(100);
    qhBoxLayout = new QHBoxLayout(this);
    horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    pbtPrevious = new QPushButton();
    pbtStartOrPause = new QPushButton();
    pbtNext = new QPushButton();
    qhBoxLayout->addItem(horizontalSpacer);
    qhBoxLayout->addWidget(pbtPrevious);
    qhBoxLayout->addWidget(pbtStartOrPause);
    qhBoxLayout->addWidget(pbtNext);
    this->setLayout(qhBoxLayout);
    retranslateUi();
}

void PlayBar::retranslateUi() {
    pbtPrevious->setIcon(QIcon("../resource/icon/previous.png"));
    pbtPrevious->setIconSize(QSize(50, 50));
    pbtStartOrPause->setIcon(QIcon("../resource/icon/start.png"));
    pbtStartOrPause->setIconSize(QSize(50, 50));
    pbtNext->setIcon(QIcon("../resource/icon/next.png"));
    pbtNext->setIconSize(QSize(50, 50));

}

QPushButton *PlayBar::getPbtPrevious() const {
    return pbtPrevious;
}

QPushButton *PlayBar::getPbtStartOrPause() const {
    return pbtStartOrPause;
}

QPushButton *PlayBar::getPbtNext() const {
    return pbtNext;
}


PlayBar::~PlayBar() = default;