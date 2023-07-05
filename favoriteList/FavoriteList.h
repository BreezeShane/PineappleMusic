//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_FAVORITELIST_H
#define PINEAPPLEMUSIC_FAVORITELIST_H

#include <QFrame>
#include <QTextEdit>
#include <QListView>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>

class FavoriteList : public QFrame
{
Q_OBJECT
private:
    QVBoxLayout *qvBoxLayout{};
    QListView *favoriteListView{};
    QPushButton *refreshList{};
    QPushButton *deleteMyfPbt{};
    QTextEdit *text{};
    QVector<QString> favoriteList{};
    QVector<QString> favoriteListLrc{};
public:
    explicit FavoriteList(QWidget *parent = nullptr);
    void setupUI();
    void updatePlayList();
    void playListUp();
    void deleteMyFavorite();

    QListView *getFavoriteListView() const;

    void setFavoriteListView(QListView *favoriteListView);

    const QVector<QString> &getFavoriteList() const;

    void setFavoriteList(const QVector<QString> &favoriteList);

    const QVector<QString> &getFavoriteListLrc() const;

    void setFavoriteListLrc(const QVector<QString> &favoriteListLrc);

    ~FavoriteList() override;
};


#endif //PINEAPPLEMUSIC_FAVORITELIST_H
