//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_MAINCONTENT_H
#define PINEAPPLEMUSIC_MAINCONTENT_H


#include <QFrame>

class MainContent : public QFrame
{
    Q_OBJECT
public:
    explicit MainContent(QWidget *parent = nullptr);
    void setupUI();
    ~MainContent() override;
};


#endif //PINEAPPLEMUSIC_MAINCONTENT_H
