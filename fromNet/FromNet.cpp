//
// Created by juncheng on 2023/6/28.
//

#include <QNetworkAccessManager>
#include "FromNet.h"
#include <QNetworkReply>
FromNet::FromNet(QWidget *parent)
        : QFrame(parent) {

    setupUI();
}

void FromNet::setupUI() {
    this->setStyleSheet("border-radius: 10px;");
    mainLayout = new QVBoxLayout;

    topLayout = new QHBoxLayout;
    keyword_input = new QLineEdit;
    keyword_input->setFixedHeight(50);
    search = new QPushButton();
    search->setIcon(QIcon("../resource/icon/search.svg"));
    search->setFixedWidth(80);

    topLayout->addWidget(keyword_input);
    topLayout->addWidget(search);


    history = new QListView;

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(history);
    this->setLayout(mainLayout);

    connect(search, SIGNAL(clicked()),
            this, SLOT(search_music()));

}

void FromNet::search_music() {
    keyword = keyword_input->text();
    auto *manager = new QNetworkAccessManager(this);
    QString base_url = "https://service-qbrcywo4-1314545420.gz.apigw.tencentcs.com/release/search/suggest?keywords=";
    QUrl url(base_url + keyword + "&type=mobile");
    QNetworkRequest request(url);

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QString response = reply->readAll();
            qDebug()<<response;
            // 处理响应数据
        } else {
            qDebug()<<"error";
            // 处理错误
        }
        reply->deleteLater();
    });
}

FromNet::~FromNet() = default;