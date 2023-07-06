//
// Created by breezeshane on 7/5/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_musicDetail.h" resolved

#include "musicDetail.h"
#include "ui_musicDetail.h"
#include <QPainter>
#include <QMap>
#include <QTextCodec>

int convertToSeconds(QString timestamp) {
    int m = timestamp.section(":", 0, 0).toInt();
    int s = timestamp.section(":", 1, 1).section(".",0,0).toInt();
    int ms = timestamp.section(":", 1, 1).section(".",1,1).toInt();
    return (m * 60 + s) * 100 + ms;
}

#include <qdebug.h>

musicDetail::musicDetail(QWidget *parent) :
        QWidget(parent), ui(new Ui::musicDetail) {
    uiBar = new PlayBar(this);
    uiBar->setupUI();
    ui->setupUi(this);
    uiBar->setGeometry(154,409,717,358);
}

//<<<<<<< HEAD
musicDetail::musicDetail(const CloudMusic& currMusic, QMediaPlayer * player, QWidget *parent) :
        QWidget(parent), ui(new Ui::musicDetail) {
//    this->setStyleSheet("background-color: transparent;border: 0px solid gray;border-radius:10px;");
    mediaPlayer = player;
//=======
//musicDetail::musicDetail(CloudMusic currMusic, QWidget *parent) :
//        QWidget(parent), ui(new Ui::musicDetail) { // on Coding...
////    qDebug()<<"music detail!";
////    qDebug()<<currMusic.getName();
////    qDebug()<<currMusic.getAlbumUrl();
//    //标题
//    this->setWindowTitle("歌词详情");
//    this->setWindowIcon(QIcon("../resource/icon/music.svg"));
//    this->setStyleSheet("background-color: transparent;border: 2px solid gray;border-radius:10px;");
//>>>>>>> fd0bdf3e850b0be4f558e771c37462e0ccff27be
    uiBar = new PlayBar(this);
    uiBar->setupUI();
    ui->setupUi(this);
    uiBar->move((this->width() - ui->verticalLayoutWidget->width()) / 2, (this->height() + 3 * ui->verticalLayoutWidget->height()) / 4);
    uiBar->resize(ui->verticalLayoutWidget->width(), ui->verticalLayoutWidget->height());

    uiBar->setAlbum(currMusic.getAlbumUrl());
    const QString& lrcFilePath = currMusic.getLrcPath();
    if (lrcFilePath == "NoLrc") {
        ui->label_1->setText("");
        ui->label_2->setText("");
        ui->label_3->setText("Ciallo~ Pineapple!");
        ui->label_4->setText("");
        ui->label_5->setText("");
    } else {
        QFile file(currMusic.getLrcPath());
        QMap<int,QString> lyricMapping;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            QTextStream in(&file);
            in.setCodec(codec);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QString timestamp = line.section(']',0,0).replace("[", "");
                int timePoint = convertToSeconds(timestamp);
                QString content = line.section(']',1,-1); // Content
                lyricMapping.insert(timePoint, content);
            }
            file.close();
        }
        map = lyricMapping;
    }
    QMap<int, QString>::iterator it = map.begin();
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &musicDetail::onPositionChanged);
}

//void musicDetail::paintEvent(QPaintEvent *event) {
//    QPainter painter(this);
//    painter.drawPixmap(0,0,1200,800, QPixmap("../resource/bgp/bgp_musicDetail.jpg"));
//}

void musicDetail::onPositionChanged(qint64 position) {
    int pos = position / 10;
    QMap<int, QString>::iterator iter = map.begin();
    while (iter != map.end())
    {
        if(pos - 50 <= iter.key() && pos + 50 >= iter.key())
        {
            qDebug() << "mapEnd.key: " << map.end().key();
            qDebug() << "iter.key: " << iter.key();
            ui->label_3->setText(iter.value());
            if (iter != map.begin()){
                ui->label_2->setText((iter - 1).value());
                if (iter - 1 == map.begin())
                    ui->label_1->setText("");
                else
                    ui->label_1->setText((iter - 2).value());
            } else {
                ui->label_1->setText("");
                ui->label_2->setText("");
            }
            if (iter != map.begin() + map.size() - 1){
                ui->label_4->setText((iter + 1).value());
                if (iter + 1 == map.begin() + map.size() - 1)
                    ui->label_5->setText("");
                else
                    ui->label_5->setText((iter + 2).value());
                break;
            } else {
                ui->label_4->setText("");
                ui->label_5->setText("");
                break;
            }
        }
        iter++;
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
