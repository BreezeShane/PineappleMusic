//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_PLAYBAR_H
#define PINEAPPLEMUSIC_PLAYBAR_H


#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>

class PlayBar : public QFrame
{
    Q_OBJECT
private:
    QHBoxLayout * qhBoxLayout{};
    QSpacerItem *horizontalSpacer{};
    QPushButton *pbtPrevious{};
    QPushButton *pbtStartOrPause{};
    QPushButton *pbtNext{};
public:
    explicit PlayBar(QWidget *parent = nullptr);
    void setupUI();
    void retranslateUi();

    QPushButton *getPbtPrevious() const;

    QPushButton *getPbtStartOrPause() const;

    QPushButton *getPbtNext() const;


    ~PlayBar() override;
};


#endif //PINEAPPLEMUSIC_PLAYBAR_H
