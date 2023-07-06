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
#include <QEventLoop>
#include <QFile>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>

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
    keyword_input->setStyleSheet("QLineEdit{"
                                 "background-color: #F5F5F5;"
                                 "border: 2px solid gray;"
                                 "background-color: transparent"
                                 "}");
    search = new QPushButton();
    search->setIcon(QIcon("../resource/icon/search.svg"));
    search->setFixedWidth(80);
    search->setStyleSheet("QPushButton {"
                        "border: 2px;"
                        "border-radius:10px;"
                        "padding: 6px;"
                        "}"
                        "QPushButton:hover {"
                        "    background-color:#FFFFF0;"
                        "}"
                        "QPushButton:pressed {"
                        "    background-color:#FFFFF0;"
                        "}");
    topLayout->addWidget(keyword_input);
    topLayout->addWidget(search);

    resultListView = new QListView;
    resultListView->setIconSize(QSize(80, 80));
    resultListView->setStyleSheet("QListView {"
                                  "background-color: #F5F5F5;"
                                  "border: 2px solid gray;"
                                  "background-color: transparent"
                                  "}"
                                  "QListView::item {"
                                  "padding: 10px;"
                                  "border-bottom: 1px solid #CCCCCC;"
                                  "}"
                                  "QListView::item:selected {"
                                  "background-color: #E0E0E0;"
                                  "}");

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(resultListView);
    this->setLayout(mainLayout);

    connect(search, SIGNAL(clicked()),
            this, SLOT(search_music()));

    QMenu* menu = new QMenu(resultListView);

    // 创建弹窗菜单项

    QAction* download = new QAction("下载", menu);

    menu->addAction(download);


// 设置ListView的setContextMenuPolicy属性
    resultListView->setContextMenuPolicy(Qt::CustomContextMenu);

// 创建customContextMenuRequested信号槽
    connect(resultListView, &QListView::customContextMenuRequested, [=](const QPoint& pos) {

        // 获取右键单击的项的索引
        QModelIndex index = resultListView->indexAt(pos);

        // 如果右键单击的位置在任何项上，则显示自定义菜单
        if (index.isValid()) {
            // 在ListView上显示自定义菜单
            menu->exec(resultListView->mapToGlobal(pos));
        }
    });


    // 创建下载项的槽函数
    connect(download, &QAction::triggered, [=]() {

//        QString filename = QFileDialog::getExistingDirectory(nullptr, "Select Directory", QDir::homePath());
//        //QString filename = QFileDialog::getSaveFileName(this,"保存文件位置",QDir::currentPath());
//        qDebug()<<filename;
//        if(filename.isNull()){
//            QMessageBox::information(this,"提示", "请输入文件名");
//            return ;
//        }
        //创建默认下载路径
        QString filename = "C:/Music";
        QDir folder(filename);
        if (!folder.exists())
        {
            folder.mkpath(".");
        }
        // 获取ListView的选中项
        QModelIndexList indexes = resultListView->selectionModel()->selectedIndexes();
        int item_index;
        int  songId;
        for (const QModelIndex& index : indexes) {
            item_index = index.row();
            // 使用索引获取项目的数据
            songId = index.data(Qt::UserRole).toInt();
        }

        QString url = "http://service-qbrcywo4-1314545420.gz.apigw.tencentcs.com/release/song/url";
        QUrlQuery query;
        query.addQueryItem("id", QString::number(songId));
        url.append("?" + query.toString());
        QNetworkRequest request(url);

        auto *manager = new QNetworkAccessManager(this);
        QNetworkReply *reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, this, [=]() {
            QString url{};
            if (reply->error() == QNetworkReply::NoError) {
                QString response = reply->readAll();
                const QString &jsonStr = response;  // 从服务器获取的 JSON 数据
                QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
                if (!doc.isNull()) {
                    QJsonObject obj = doc.object();
                    if (obj.contains("data")) {
                        QJsonArray data = obj["data"].toArray();
                        if (!data.isEmpty()) {
                            QJsonObject item = data[0].toObject();
                            if (item.contains("url")) {
                                url = item["url"].toString();
                                current_music_url = url;
                                qDebug() << "download file";
                                //下载路径
                                downloadFile(current_music_url,filename + "/"+songs.at(item_index).name+".mp3");
                            }
                        }
                    }
                }
                // 处理响应数据
            } else {
                qDebug() << "error";
                // 处理错误
            }
            reply->deleteLater();

        });
        qDebug() << "Double clicked on item " << item_index << ": " << songId;

    });

}

void FromNet::search_music() {
    songs.clear();
    keyword = keyword_input->text();
    auto *manager = new QNetworkAccessManager(this);
    QString url = "http://service-qbrcywo4-1314545420.gz.apigw.tencentcs.com/release/search";
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
        qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
        qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();

    });
}

void FromNet::updateResultView() {
// 创建一个数据模型
    QStandardItemModel *model = new QStandardItemModel(this);
// 遍历所有歌曲，将其转换为 QStandardItem 对象，并添加到数据模型中
    for (int i = 0; i < songs.size(); i++) {
        Song song = songs.at(i);
        // 创建一个 QStandardItem 对象，并设置其数据
        auto *item = new QStandardItem();
        //加载专辑图
        auto *manager = new QNetworkAccessManager(this);
        QUrl url(song.album.artist.img1v1Url);
        QNetworkRequest request(url);
        QNetworkReply *reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray data = reply->readAll();
                QPixmap pixmap;
                pixmap.loadFromData(data);
                // 将pixmap显示在UI上
                item->setIcon(QIcon(pixmap));
            } else {
                // 处理错误情况
                qWarning()<<"can not load album"<<url;
            }
        });
        //设置歌曲信息
        item->setText(song.name.append("-").append(song.artists.first().name));
        // 设置歌曲 ID 为 UserRole
        item->setData(song.id, Qt::UserRole);

        // 将艺术家信息转换为字符串，并设置为 QStandardItem 对象的子项
        QString artistText = song.artists.first().name;
        // 使用 setData() 函数来设置不同角色的数据
        item->setData(artistText, Qt::UserRole + 1);

        // 将专辑信息转换为字符串，并设置为 QStandardItem 对象的子项
        QString albumText = song.album.artist.img1v1Url;
        // 使用 setData() 函数来设置不同角色的数据
        item->setData(albumText, Qt::UserRole + 2);

        // 将专辑信息转换为字符串，并设置为 QStandardItem 对象的子项
        int duration = song.duration;
        // 使用 setData() 函数来设置不同角色的数据
        item->setData(duration, Qt::UserRole + 3);
        item->setData(song.name, Qt::UserRole+4);
        // 将 QStandardItem 对象添加到数据模型中
        model->appendRow(item);
    }

    // 将数据模型设置为 QListView 的模型
    resultListView->setModel(model);
}

void FromNet::downloadFile(const QUrl &url, const QString &filePath) {
    auto *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(url));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if(reply->error()) {
        // 处理错误
    } else {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();

            // 在文件下载完成后，创建 QTimer 对象，定时显示提示框
            QTimer::singleShot(500, this, [=](){
                QMessageBox::information(nullptr, "下载完成", "文件已下载完成！");
            });
        }
    }

    reply->deleteLater();
    manager->deleteLater();
}


FromNet::~FromNet() = default;