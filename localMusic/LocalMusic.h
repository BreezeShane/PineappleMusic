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
    QSpacerItem *horizontalSpacer{};
    QListView *musicListView{};
    QFile *localPlayListFile{};
    QVector<QString> playList{};
    QVector<QString> playListLrc{};


public:
    explicit LocalMusic(QWidget *parent = nullptr);

    void setupUI();

    void retranslateUi();

    void updateMusicList();

    QListView *getMusicListView() const;

    const QVector<QString> &getPlayList() const;

    const QVector<QString> &getPlayListLrc() const; //歌词文件列表

    ~LocalMusic() override;

public slots:

    void scanLocalMusic();
};


#endif //PINEAPPLEMUSIC_LOCALMUSIC_H
