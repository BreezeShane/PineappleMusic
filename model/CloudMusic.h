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
    static Song fromJson(const QJsonObject &songObject);
};

class CloudMusic {
private:
    QString name;  // 歌曲名称
    QString album_url;  // 专辑封面 URL
    QString artist;  // 专辑所属艺术家
    QString music_url;//音乐网络地址
    QString lrc_path;//歌词文件路径
    int duration;  // 歌曲时长（毫秒）
    QString position_time; //播放进度
public:
    const QString &getName() const;

    void setName(const QString &name);

    const QString &getAlbumUrl() const;

    void setAlbumUrl(const QString &albumUrl);

    const QString &getArtist() const;

    void setArtist(const QString &artist);

    const QString &getMusicUrl() const;

    void setMusicUrl(const QString &musicUrl);

    int getDuration() const;

    void setDuration(int duration);

    const QString &getLrcPath() const;

    void setLrcPath(const QString &lrcPath);

    const QString &getPositionTime() const;

    void setPositionTime(const QString &positionTime);
};


#endif //PINEAPPLEMUSIC_CLOUDMUSIC_H
