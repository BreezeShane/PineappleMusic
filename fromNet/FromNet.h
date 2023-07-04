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

class FromNet : public QFrame
{
Q_OBJECT
private:

public:
    explicit FromNet(QWidget *parent = nullptr);
    void setupUI();
    QVBoxLayout* mainLayout{};

    QHBoxLayout* topLayout{};
    QLineEdit* keyword_input{};
    QPushButton* search{};
    QListView *history{};
    QString keyword{};
    ~FromNet() override;
public slots:
    void search_music();
};

#endif //PINEAPPLEMUSIC_FROMNET_H