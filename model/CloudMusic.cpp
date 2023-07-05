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


const QString &CloudMusic::getName() const {
    return name;
}

void CloudMusic::setName(const QString &name) {
    CloudMusic::name = name;
}

const QString &CloudMusic::getAlbumUrl() const {
    return album_url;
}

void CloudMusic::setAlbumUrl(const QString &albumUrl) {
    album_url = albumUrl;
}

const QString &CloudMusic::getArtist() const {
    return artist;
}

void CloudMusic::setArtist(const QString &artist) {
    CloudMusic::artist = artist;
}

const QString &CloudMusic::getMusicUrl() const {
    return music_url;
}

void CloudMusic::setMusicUrl(const QString &musicUrl) {
    music_url = musicUrl;
}

int CloudMusic::getDuration() const {
    return duration;
}

void CloudMusic::setDuration(int duration) {
    CloudMusic::duration = duration;
}
