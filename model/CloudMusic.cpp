//
// Created by juncheng on 2023/7/4.
//

#include <QJsonArray>
#include "CloudMusic.h"

Song Song::fromJson(const QJsonObject& songObject)
{
    Song song;

    // 解析歌曲信息
    song.id = songObject["id"].toInt();
    song.name = songObject["name"].toString();
    song.duration = songObject["duration"].toInt();
    song.mvId = songObject["mvid"].toInt();
    song.isPaid = songObject["fee"].toInt() != 0;

    // 解析艺术家信息
    QList<Artist> artists;
    QJsonArray artistArray = songObject["artists"].toArray();
    for (int i = 0; i < artistArray.size(); i++) {
        QJsonObject artistObject = artistArray[i].toObject();
        Artist artist;
        artist.id = artistObject["id"].toInt();
        artist.name = artistObject["name"].toString();
        artist.img1v1Url = artistObject["img1v1Url"].toString();
        artists.append(artist);
    }
    song.artists = artists;

    // 解析专辑信息
    QJsonObject albumObject = songObject["album"].toObject();
    Album album;
    album.id = albumObject["id"].toInt();
    album.name = albumObject["name"].toString();
    album.img1v1Url = albumObject["img1v1Url"].toString();
    QJsonObject artistObject = albumObject["artist"].toObject();
    album.artist.id = artistObject["id"].toInt();
    album.artist.name = artistObject["name"].toString();
    album.artist.img1v1Url = artistObject["img1v1Url"].toString();
    song.album = album;

    return song;
}
