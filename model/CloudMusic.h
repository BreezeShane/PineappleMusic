//
// Created by juncheng on 2023/7/4.
//

#ifndef PINEAPPLEMUSIC_CLOUDMUSIC_H
#define PINEAPPLEMUSIC_CLOUDMUSIC_H

#include <QString>
#include <QVector>
#include <QJsonObject>

class Artist {
public:
    int id;  // 艺术家 ID
    QString name;  // 艺术家名称
    QString img1v1Url;  // 艺术家头像 URL
};

class Album {
public:
    int id;  // 专辑 ID
    QString name;  // 专辑名称
    QString img1v1Url;  // 专辑封面 URL
    Artist artist;  // 专辑所属艺术家
};

class Song {
public:
    int id;  // 歌曲 ID
    QString name;  // 歌曲名称
    QList<Artist> artists;  // 艺术家列表
    Album album;  // 所属专辑
    int duration;  // 歌曲时长（毫秒）
    int mvId;  // MV ID
    bool isPaid;  // 是否付费

    // 解析 JSON 数据为 Song 类实例
    static Song fromJson(const QJsonObject& songObject);
};

class CloudMusic {

};


#endif //PINEAPPLEMUSIC_CLOUDMUSIC_H
