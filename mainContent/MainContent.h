//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_MAINCONTENT_H
#define PINEAPPLEMUSIC_MAINCONTENT_H


#include <QFrame>
#include <QStackedWidget>
#include <QHBoxLayout>
#include "localMusic/LocalMusic.h"
#include "playList/PlayList.h"
#include "fromNet/FromNet.h"
#include "chatroom/Chatroom.h"
class MainContent : public QFrame
{
    Q_OBJECT
private:
    QHBoxLayout * qhBoxLayout{};
    QStackedWidget *contentPages{};
    LocalMusic* localMusicPage;
    PlayList* playListPage;
    FromNet* fromNetPage;
    Chatroom* chatroomPage;
public:
    QStackedWidget *getContentPages() const;

    explicit MainContent(QWidget *parent = nullptr);
    void setupUI();
    void initContentPages();

    LocalMusic *getLocalMusicPage() const;

    void setLocalMusicPage(LocalMusic *localMusicPage);

    PlayList *getPlayListPage() const;

    void setPlayListPage(PlayList *playListPage);

    FromNet *getFromNetPage() const;

    void setFromNetPage(FromNet *fromNetPage);

    ~MainContent() override;
};


#endif //PINEAPPLEMUSIC_MAINCONTENT_H
