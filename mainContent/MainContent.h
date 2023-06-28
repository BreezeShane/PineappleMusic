//
// Created by juncheng on 2023/6/27.
//

#ifndef PINEAPPLEMUSIC_MAINCONTENT_H
#define PINEAPPLEMUSIC_MAINCONTENT_H


#include <QFrame>
#include <QStackedWidget>
#include <QHBoxLayout>

class MainContent : public QFrame
{
    Q_OBJECT
private:
    QHBoxLayout * qhBoxLayout{};
    QStackedWidget *contentPages{};

public:
    QStackedWidget *getContentPages() const;

    explicit MainContent(QWidget *parent = nullptr);
    void setupUI();
    void initContentPages();
    ~MainContent() override;
};


#endif //PINEAPPLEMUSIC_MAINCONTENT_H
