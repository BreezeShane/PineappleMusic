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


musicDetail::musicDetail(const CloudMusic& currMusic, QMediaPlayer * player, QWidget *parent) :
        QWidget(parent), ui(new Ui::musicDetail) {
    mediaPlayer = player;
    this->setWindowTitle("歌词详情");
    this->setWindowIcon(QIcon("../resource/icon/disk.svg"));

    uiBar = new PlayBar(this);
    uiBar->setupUI();
    ui->setupUi(this);
    uiBar->move((this->width() - ui->verticalLayoutWidget->width()) / 2, (this->height() + 3 * ui->verticalLayoutWidget->height()) / 4);
    uiBar->resize(ui->verticalLayoutWidget->width(), ui->verticalLayoutWidget->height());

    //设置颜色
    uiBar->setStyleSheet("background-color: white;border: 0px solid gray;border-radius:10px;");
    QPalette palette1 = ui->label_1->palette();  // 获取label的调色板
    palette1.setColor(QPalette::WindowText, Qt::white);  // 设置文字颜色为白色
    ui->label_1->setPalette(palette1);  // 应用修改后的调色板到label

    QPalette palette2 = ui->label_2->palette();  // 获取label的调色板
    palette2.setColor(QPalette::WindowText, Qt::white);
    ui->label_2->setPalette(palette2);  // 应用修改后的调色板到label

    QPalette palette3 = ui->label_3->palette();  // 获取label的调色板
    palette3.setColor(QPalette::WindowText, Qt::white);
    ui->label_3->setPalette(palette3);  // 应用修改后的调色板到label

    QPalette palette4 = ui->label_4->palette();  // 获取label的调色板
    palette4.setColor(QPalette::WindowText, Qt::white);
    ui->label_4->setPalette(palette4);  // 应用修改后的调色板到label

    QPalette palette5 = ui->label_5->palette();  // 获取label的调色板
    palette5.setColor(QPalette::WindowText, Qt::white);
    ui->label_5->setPalette(palette5);  // 应用修改后的调色板到label
    // 设置布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ui->label_1);
    mainLayout->addWidget(ui->label_2);
    mainLayout->addWidget(ui->label_3);
    mainLayout->addWidget(ui->label_4);
    mainLayout->addWidget(ui->label_5);
    mainLayout->addWidget(uiBar);
    ui->verticalLayoutWidget->setLayout(mainLayout);

    uiBar->setAlbum(currMusic.getAlbumUrl());
//    QFile file(currMusic.getLrcPath());
    file=new QFile;
    file->setFileName(currMusic.getLrcPath());
    qDebug()<<currMusic.getLrcPath()<<"文件";
    const QString& lrcFilePath = currMusic.getLrcPath();
    if (lrcFilePath == "NoLrc") {
        ui->label_1->setText("");
        ui->label_2->setText("");
        ui->label_3->setText("Ciallo~ Pineapple!");
        ui->label_4->setText("");
        ui->label_5->setText("");
    } else {
        QMap<int,QString> lyricMapping;
        if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            QTextStream in(file);
            in.setCodec(codec);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QString timestamp = line.section(']',0,0).replace("[", "");
                int timePoint = convertToSeconds(timestamp);
                QString content = line.section(']',1,-1); // Content
                lyricMapping.insert(timePoint, content);
            }
            file->close();
        }
        map = lyricMapping;
    }
    QMap<int, QString>::iterator it = map.begin();
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &musicDetail::onPositionChanged);
}
void musicDetail::showEvent(QShowEvent *event) {

}

void musicDetail::onPositionChanged(qint64 position) {
    int pos = position / 10;
   // map.clear();  // 清除QMap中的所有元素
    QMap<int, QString>::iterator iter = map.begin();  // 获取指向QMap开头位置的迭代器
//    QMap<int, QString>::iterator iter = map.begin();
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
