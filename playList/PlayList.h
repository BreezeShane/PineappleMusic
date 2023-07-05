//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_PLAYLIST_H
#define PINEAPPLEMUSIC_PLAYLIST_H

#include <QFrame>
#include <QTextEdit>
#include <QListView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>

class PlayList : public QFrame
{
Q_OBJECT
private:
    QVBoxLayout *playLayout{};
    QListView *playListView{};
    QPushButton *playMusicPbt{};
    QTextEdit *text{};
    QVector<QString> musicPlay{};
    QVector<QString> playListLrc{};
public:
    explicit PlayList(QWidget *parent = nullptr);
    void setupUI();
    void updatePlayList();
    void playListUp();
    QListView *getPlayMusicListView() const;

    const QVector<QString> &getPlayMusicList() const;

    const QVector<QString> &getPlayMusicListLrc() const; //歌词文件列表
    ~PlayList() override;
};


#endif //PINEAPPLEMUSIC_PLAYLIST_H
