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
    album = new QLabel();
    album->setMouseTracking(true);
    pbtModel = new QPushButton();
    pbtPrevious = new QPushButton();
    pbtStartOrPause = new QPushButton();
    pbtNext = new QPushButton();
    currentProcess = new QLabel();
    finalProcess = new QLabel();
    slider = new MySlider(Qt::Horizontal, this);

    currentProcess->setText("00:00");
    finalProcess->setText("00:00");
    currentProcess->setFixedSize(50,50);//设置大小
    finalProcess->setFixedSize(50,50);
    currentProcess->setStyleSheet("QLabel {"
                                  "background-color: transparent;"
                                  //"border: 1px solid gray;"
                                  "border: none;" //隐藏边框
                                  "border-radius: 4px;"
                                  "padding: 2px;"
                                  "}");

    finalProcess->setStyleSheet("QLabel {"
                                "background-color: transparent;"
                                //"border: 1px solid gray;"
                                "border: none;"
                                "border-radius: 4px;"
                                "padding: 2px;"
                                "}");

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

    qhBoxLayout->addWidget(album);
    qhBoxLayout->addWidget(currentProcess);
    qhBoxLayout->addWidget(slider);
    qhBoxLayout->addWidget(finalProcess);
    qhBoxLayout->addWidget(pbtModel);
    qhBoxLayout->addWidget(pbtPrevious);
    qhBoxLayout->addWidget(pbtStartOrPause);
    qhBoxLayout->addWidget(pbtNext);

    this->setLayout(qhBoxLayout);
    retranslateUi();
}

void PlayBar::retranslateUi() {
    QPixmap pixmap("../resource/icon/default_album.svg");
    QSize size(60, 60);
    QPixmap scaledPixmap = pixmap.scaled(size, Qt::KeepAspectRatio, Qt::FastTransformation);
    album->setPixmap(scaledPixmap);

    pbtModel->setText("顺序播放");
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

MySlider *PlayBar::getSlider() const {
    return slider;
}

QLabel * PlayBar::getCurrentProcess() const {
    return currentProcess;
}

QLabel * PlayBar::getFinalProcess() const {
    return finalProcess;
}

QPushButton *PlayBar::getPbtModel() const {
    return pbtModel;
}

PlayBar::~PlayBar() = default;