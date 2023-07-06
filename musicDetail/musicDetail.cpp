//
// Created by breezeshane on 7/5/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_musicDetail.h" resolved

#include "musicDetail.h"
#include "ui_musicDetail.h"
#include <QPainter>
#include <QVBoxLayout>


#include <qdebug.h>

musicDetail::musicDetail(QWidget *parent) :
        QWidget(parent), ui(new Ui::musicDetail) {
    uiBar = new PlayBar(this);
    uiBar->setupUI();
    ui->setupUi(this);
    uiBar->setGeometry(154,409,717,358);
    ui->textBrowser->setStyleSheet("text-align: center;");
    ui->textBrowser->setHtml(QString("<html><head><style>body {text-align: center;}</style></head>"
                                     "<body>%1</body></html>").arg("Ciallo~ Pineapple!"));
}

musicDetail::musicDetail(CloudMusic currMusic, QWidget *parent) :
        QWidget(parent), ui(new Ui::musicDetail) { // on Coding...
//    qDebug()<<"music detail!";
//    qDebug()<<currMusic.getName();
//    qDebug()<<currMusic.getAlbumUrl();
    //标题
    this->setWindowTitle("歌词详情");
    this->setWindowIcon(QIcon("../resource/icon/music.svg"));
    this->setStyleSheet("background-color: transparent;border: 2px solid gray;border-radius:10px;");
    uiBar = new PlayBar(this);
    uiBar->setupUI();
    ui->setupUi(this);
    uiBar->setGeometry(154,409,717,358);
    ui->textBrowser->setStyleSheet("text-align: center;margin-top:20px");

    uiBar->setAlbum(currMusic.getAlbumUrl());
//    QFile lyricsFile(currMusic.getLrcPath());
//    lyricsFile.open(QIODevice::ReadOnly | QIODevice::Text);
    qDebug() << currMusic.getLrcPath();
    const QString& lrcFilePath = currMusic.getLrcPath();
    if (lrcFilePath == "NoLrc") {
        ui->textBrowser->setHtml(QString("<html><head><style>body {text-align: center;}</style></head>"
                                         "<body>%1</body></html>").arg("Ciallo~ Pineapple!"));
    } else {
        ui->textBrowser->setSource(QUrl::fromLocalFile(currMusic.getLrcPath()));
        ui->textBrowser->show();
    }

}

void musicDetail::paintEvent(QPaintEvent *event) {
    // 设置背景图的样式
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(QPixmap("../resource/image/17.jpg")));
    this->setPalette(palette);
}

musicDetail::~musicDetail() {
    delete ui;
}
