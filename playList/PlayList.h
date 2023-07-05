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
//    QFile *musicPlaylist{};
    QVector<QString> musicPlay{};
public:
    explicit PlayList(QWidget *parent = nullptr);
    void setupUI();
    void updatePlayList();
    void playListUp();

    ~PlayList() override;
};


#endif //PINEAPPLEMUSIC_PLAYLIST_H
