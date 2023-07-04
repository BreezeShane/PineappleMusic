//
// Created by juncheng on 2023/6/28.
//

#include "FromNet.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QLineEdit>
#include <QDockWidget>
#include <QFontDialog>
#include <QTextEdit>
#include <QListView>
#include <QStringListModel>
#include <QUrl>


FromNet::FromNet(QWidget *parent)
        : QFrame(parent) {

    setupUI();

    connect(find,&QPushButton::clicked,this, &FromNet::on_find_cliked);
}

void FromNet::setupUI() {
    this->setStyleSheet("border-radius: 10px;border: 1px solid gray");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    //搜索框
    QWidget *url_area = new QWidget(this);
    url_area->setFixedHeight(80);
    QHBoxLayout *url_layout = new QHBoxLayout(url_area);

    url_in = new QLineEdit;
    url_in->setFixedSize(500,30);
    find = new QPushButton("Find");
    find->setFixedSize(120,30);
    download = new QPushButton("download");
    download->setFixedSize(120,30);

    url_layout->addWidget(url_in);
    url_layout->addWidget(find);
    url_layout->addWidget(download);

    //搜索结果显示
    QWidget *result = new QWidget(this);
    QLabel *result_label = new QLabel("搜索结果：");
    result_label->setFixedSize(80,30);
    //result->setFixedHeight(200);
    QVBoxLayout *result_layout = new QVBoxLayout(result);
    QListView *result_view = new QListView;
    //result_view->setFixedSize(this->width(),300);
    result_layout->addWidget(result_label);
    result_layout->addWidget(result_view);

    //历史搜索结果
    QWidget *history = new QWidget(this);
    QLabel *history_label = new QLabel("历史搜索：");
    history_label->setFixedSize(80,30);

    QVBoxLayout *history_layout = new QVBoxLayout(history);
    QListView *history_view = new QListView;

    history_layout->addWidget(history_label);
    history_layout->addWidget(history_view);

    mainLayout->addWidget(url_area);
    mainLayout->addWidget(result);
    mainLayout->addWidget(history);


    QStringList items;
    items << "Item 1" << "Item 2" << "Item 3";

    QStringListModel *model = new QStringListModel(items);

    result_view->setModel(model);

}

void FromNet::on_find_cliked() {
//    qDebug()<<"播放"<<endl;
//    QString url_text = url_in->text();
//    if(url_text == NULL){
//        QMessageBox::information(this,"提示","请输入url");
//        return ;
//    }
//    QMediaPlayer *player = new QMediaPlayer;
//    QUrl url(url_text);
//    player->setMedia(url);
//    player->play();

}

void FromNet::on_download_cliked() {


}

QPushButton *FromNet::getFindButton() const {
    return find;
}

QLineEdit *FromNet::geturl_in() const {
    return url_in;
}


FromNet::~FromNet() = default;