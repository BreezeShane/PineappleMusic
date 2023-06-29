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

class LocalMusic : public QFrame
{
Q_OBJECT
private:
    QVBoxLayout *verticalLayout{};
    QHBoxLayout *horizontalLayout{};
    QPushButton *reloadMusicPbt{};
    QSpacerItem *horizontalSpacer{};
    QListView *musicListView{};
public:
    explicit LocalMusic(QWidget *parent = nullptr);
    void setupUI();
    void retranslateUi();
    ~LocalMusic() override;
};



#endif //PINEAPPLEMUSIC_LOCALMUSIC_H
