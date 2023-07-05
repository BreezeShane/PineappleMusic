//
// Created by juncheng on 2023/6/28.
//

#include <QNetworkAccessManager>
#include "FromNet.h"
#include "model/CloudMusic.h"
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>

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


    resultListView = new QListView;

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(resultListView);
    this->setLayout(mainLayout);

    connect(search, SIGNAL(clicked()),
            this, SLOT(search_music()));

}

void FromNet::search_music() {
    keyword = keyword_input->text();
    auto *manager = new QNetworkAccessManager(this);
    QString url = "https://service-qbrcywo4-1314545420.gz.apigw.tencentcs.com/release/search";
    QUrlQuery query;
    query.addQueryItem("keywords", keyword);
    query.addQueryItem("limit", "2");
    url.append("?" + query.toString());
    QNetworkRequest request(url);

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QString response = reply->readAll();
            const QString &jsonStr = response;  // 从服务器获取的 JSON 数据
            QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
            QJsonObject resultObject = doc.object()["result"].toObject();
            QJsonArray songsArray = resultObject["songs"].toArray();
            for (int i = 0; i < songsArray.size(); i++) {
                QJsonObject songObject = songsArray[i].toObject();
                Song song = Song::fromJson(songObject);
                songs.append(song);
            }
            // 处理响应数据
        } else {
            qDebug() << "error";
            // 处理错误
        }
        reply->deleteLater();
        updateResultView();//搜索事件结束，更新列表，显示结果
    });
}

void FromNet::updateResultView() {
// 创建一个数据模型
    QStandardItemModel *model = new QStandardItemModel(this);

// 遍历所有歌曲，将其转换为 QStandardItem 对象，并添加到数据模型中
    for (int i = 0; i < songs.size(); i++) {
        Song song = songs.at(i);

        // 创建一个 QStandardItem 对象，并设置其数据
        // 创建一个 QStandardItem 对象，并设置其数据
        auto *item = new QStandardItem();
        item->setText(song.name.append("-").append(song.artists.first().name));
//        // 设置歌曲 ID 为 UserRole
//        item->setData(song.id, Qt::UserRole);
//
//        // 将艺术家信息转换为字符串，并设置为 QStandardItem 对象的子项
//        QString artistText;
//        for (int j = 0; j < song.artists.size(); j++) {
//            Artist artist = song.artists.at(j);
//            if (!artistText.isEmpty()) {
//                artistText += " / ";
//            }
//            artistText += artist.name;
//        }
//        // 使用 setData() 函数来设置不同角色的数据
//        item->setData(artistText, Qt::UserRole + 1);
//
//        // 将专辑信息转换为字符串，并设置为 QStandardItem 对象的子项
//        QString albumText = song.album.name;
//        // 使用 setData() 函数来设置不同角色的数据
//        item->setData(albumText, Qt::UserRole + 2);

        // 将 QStandardItem 对象添加到数据模型中
        model->appendRow(item);
    }

    // 将数据模型设置为 QListView 的模型
    resultListView->setModel(model);
}

FromNet::~FromNet() = default;