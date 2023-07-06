//
// Created by juncheng on 2023/7/6.
//

#ifndef PINEAPPLEMUSIC_PLAYLIST_H
#define PINEAPPLEMUSIC_PLAYLIST_H

#include <QFrame>
#include <QListView>
#include <QVBoxLayout>
class PlayList : public QFrame
{
Q_OBJECT
private:
    QVBoxLayout* mainLayout{};
    QListView* playListView{};
    QVector<QString> currentPlaylistName{};     //当前播放列表
    QString currentPlayName{};  //当前正在播放的音乐名称
public:
    explicit PlayList(QWidget *parent = nullptr);
    void setupUI();

    QListView *getPlayListView() const;

    const QString &getCurrentPlayName() const;

    void setCurrentPlayName(const QString &currentPlayName);

    const QVector<QString> &getCurrentPlaylistName() const;

    void setCurrentPlaylistName(const QVector<QString> &currentPlaylistName);

    ~PlayList() override;
protected:
    void showEvent(QShowEvent *event) override;

    void hideEvent(QHideEvent *event) override;
};

#endif //PINEAPPLEMUSIC_PLAYLIST_H
