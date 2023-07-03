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
    currentProcess = new QLabel();
    finalProcess = new QLabel();
    slider = new QSlider(Qt::Horizontal, this);
    slider->setStyleSheet("QSlider::groove:horizontal {"    //修改进度条样式
                          "border: none;"
                          "height: 8px;"
                          "border-radius: 0px;"
                          "background: lightgray;"
                          "}"
                          "QSlider::handle:horizontal {"
                          "background: rgb(255, 120, 0);"
                          "border: none;"
                          "width: 16px;"
                          "height: 16px;"
                          "margin: -5px 0;"
                          "border-radius: 8px;"
                          "}"
                          "QSlider::sub-page:horizontal {"
                          "height: 4px;"
                          "border-radius: 3px;"
                          "background: rgb(255, 170, 0);"
                          "}"
                          "QSlider::add-page:horizontal {"
                          "height: 4px;"
                          "border-radius: 3px;"
                          "background: lightgray;"
                          "}");

    qhBoxLayout->addItem(horizontalSpacer);
    qhBoxLayout->addWidget(currentProcess);
    qhBoxLayout->addWidget(slider);
    qhBoxLayout->addWidget(finalProcess);
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

QSlider *PlayBar::getSlider() const {
    return slider;
}

QLabel * PlayBar::getCurrentProcess() const {
    return currentProcess;
}

QLabel * PlayBar::getFinalProcess() const {
    return finalProcess;
}
PlayBar::~PlayBar() = default;