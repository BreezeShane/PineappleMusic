//
// Created by juncheng on 2023/6/28.
//

#ifndef PINEAPPLEMUSIC_FROMNET_H
#define PINEAPPLEMUSIC_FROMNET_H

#include <QFrame>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLineEdit>
#include <QSettings>

class FromNet : public QFrame
{
Q_OBJECT
public:
    explicit FromNet(QWidget *parent = nullptr);
    void setupUI();

    QPushButton *getFindButton() const;

    QLineEdit *geturl_in() const;

private slots:
    void on_find_clicked();

    void on_download_clicked();




private:
    QPushButton *find;
    QPushButton *downloads;
    QLineEdit *url_in;
    QMediaPlayer *player;



    ~FromNet() override;
};

#endif //PINEAPPLEMUSIC_FROMNET_H
