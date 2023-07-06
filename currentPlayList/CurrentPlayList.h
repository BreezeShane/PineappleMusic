//
// Created by juncheng on 2023/7/6.
//

#ifndef PINEAPPLEMUSIC_CURRENTPLAYLIST_H
#define PINEAPPLEMUSIC_CURRENTPLAYLIST_H

#include <QFrame>
#include <QListView>
#include <QVBoxLayout>
class CurrentPlayList : public QFrame
{
Q_OBJECT
private:
    QVBoxLayout* mainLayout{};
    QListView* playListView{};
    QVector<QString> currentPlaylistName{};     //当前播放列表
    QVector<QString> currentPlaylist{};     //当前播放列表
    QVector<QString> currentPlaylistLrc{};  //当前播放列表对应的歌词文件列表，没有歌词文件，存储内容为 NoLrc
    QString currentPlayName{};  //当前正在播放的音乐名称
    QString currentPlay{};  //当前正在播放的音乐路径
    QString currentPlayLrc{};   //当前播放音乐的lrc歌词文件路径
public:
    explicit CurrentPlayList(QWidget *parent = nullptr);
    void setupUI();

    QListView *getPlayListView() const;

    const QString &getCurrentPlayName() const;

    void setCurrentPlayName(const QString &currentPlayName);

    const QVector<QString> &getCurrentPlaylistName() const;

    void setCurrentPlaylistName(const QVector<QString> &currentPlaylistName);

    void setPlayListView(QListView *playListView);

    const QVector<QString> &getCurrentPlaylist() const;

    void setCurrentPlaylist(const QVector<QString> &currentPlaylist);

    const QVector<QString> &getCurrentPlaylistLrc() const;

    void setCurrentPlaylistLrc(const QVector<QString> &currentPlaylistLrc);

    const QString &getCurrentPlay() const;

    void setCurrentPlay(const QString &currentPlay);

    const QString &getCurrentPlayLrc() const;

    void setCurrentPlayLrc(const QString &currentPlayLrc);

    ~CurrentPlayList() override;
protected:
    void showEvent(QShowEvent *event) override;

    void hideEvent(QHideEvent *event) override;
};

#endif //PINEAPPLEMUSIC_CURRENTPLAYLIST_H
