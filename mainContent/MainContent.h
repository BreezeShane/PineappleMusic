//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_MAINCONTENT_H
#define PINEAPPLEMUSIC_MAINCONTENT_H


#include <QFrame>
#include <QStackedWidget>
#include <QHBoxLayout>
#include "localMusic/LocalMusic.h"
#include "favoriteList/FavoriteList.h"
#include "fromNet/FromNet.h"
#include "chatroom/Chatroom.h"
#include "playList/PlayList.h"
class MainContent : public QFrame
{
    Q_OBJECT
private:
    QHBoxLayout * qhBoxLayout{};
    QStackedWidget *contentPages{};
    LocalMusic* localMusicPage;
    FavoriteList* favoriteListPage;
    FromNet* fromNetPage;
    Chatroom* chatroomPage;
    PlayList* playListPage;
public:
    QStackedWidget *getContentPages() const;

    explicit MainContent(QWidget *parent = nullptr);
    void setupUI();
    void initContentPages();

    LocalMusic *getLocalMusicPage() const;

    void setLocalMusicPage(LocalMusic *localMusicPage);

    FavoriteList *getFavoriteListPage() const;

    void setFavoriteListPage(FavoriteList *favoriteListPage);

    Chatroom *getChatroomPage() const;

    void setChatroomPage(Chatroom *chatroomPage);

    PlayList *getPlayListPage() const;

    void setPlayListPage(PlayList *playListPage);

    FromNet *getFromNetPage() const;

    void setFromNetPage(FromNet *fromNetPage);

    ~MainContent() override;
};


#endif //PINEAPPLEMUSIC_MAINCONTENT_H
