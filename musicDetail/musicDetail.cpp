//
// Created by breezeshane on 7/5/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_musicDetail.h" resolved

#include "musicDetail.h"
#include "ui_musicDetail.h"
#include <QPainter>

#include <qdebug.h>

musicDetail::musicDetail(QWidget *parent) :
        QWidget(parent), ui(new Ui::musicDetail) {
    ui->setupUi(this);
}

void musicDetail::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0,0,1024,512, QPixmap("../resource/bgp/bgp_musicDetail.jpg"));
}

musicDetail::~musicDetail() {
    delete ui;
}
