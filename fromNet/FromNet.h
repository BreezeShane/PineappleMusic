//
// Created by juncheng on 2023/6/28.
//

#ifndef PINEAPPLEMUSIC_FROMNET_H
#define PINEAPPLEMUSIC_FROMNET_H

#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListView>
#include <QLabel>
#include "model/CloudMusic.h"

class FromNet : public QFrame
{
Q_OBJECT
private:
    QList<Song> songs;
    QString current_music_url;
public:
    explicit FromNet(QWidget *parent = nullptr);
    void setupUI();
    QVBoxLayout* mainLayout{};

    QHBoxLayout* topLayout{};
    QLineEdit* keyword_input{};
    QPushButton* search{};
    QListView *resultListView{};
    QString keyword{};
    void downloadFile(const QUrl &url, const QString &filePath);

    void updateResultView();
    ~FromNet() override;
public slots:
    void search_music();
};

#endif //PINEAPPLEMUSIC_FROMNET_H