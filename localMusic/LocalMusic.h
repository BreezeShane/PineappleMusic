//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_LOCALMUSIC_H
#define PINEAPPLEMUSIC_LOCALMUSIC_H


#include <QFrame>
#include <QPushButton>
#include <QSpacerItem>
#include <QListView>
#include <QVBoxLayout>
#include <QFile>
#include <QMediaPlayer>
#include <QMediaMetaData>
class LocalMusic : public QFrame {
Q_OBJECT
private:
    QVBoxLayout *verticalLayout{};
    QHBoxLayout *horizontalLayout{};
    QPushButton *reloadMusicPbt{};
    QPushButton *addMusicPlayPbt{};
    QSpacerItem *horizontalSpacer{};
    QListView *musicListView{};
    QFile *localPlayListFile{};
    QFile *favoriteListFile{};
    QVector<QString> localMusicListName{};
    QVector<QString> localMusicList{};
    QVector<QString> localMusicListLrc{};
    QString currentPlay{};  //当前正在播放的音乐路径
    QString currentPlayLrc{};  //当前正在播放的歌词路径


public:
    explicit LocalMusic(QWidget *parent = nullptr);

    void setupUI();

    void retranslateUi();

    void updateMusicList();
    void addMusicToPlaylist();

    QListView *getMusicListView() const;

    const QVector<QString> &getPlayList() const;

    const QVector<QString> &getPlayListLrc() const; //歌词文件列表
    const QVector<QString> &getLocalMusicListName() const;

    void setLocalMusicListName(const QVector<QString> &localMusicListName);

    ~LocalMusic() override;

public slots:

    void scanLocalMusic();
};


#endif //PINEAPPLEMUSIC_LOCALMUSIC_H
