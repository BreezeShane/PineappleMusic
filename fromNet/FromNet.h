//
// Created by juncheng on 2023/6/28.
//

#ifndef PINEAPPLEMUSIC_FROMNET_H
#define PINEAPPLEMUSIC_FROMNET_H

#include <QFrame>

class FromNet : public QFrame
{
Q_OBJECT
public:
    explicit FromNet(QWidget *parent = nullptr);
    void setupUI();

    ~FromNet() override;
};

#endif //PINEAPPLEMUSIC_FROMNET_H
