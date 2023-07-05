//
// Created by breezeshane on 7/5/23.
//

#ifndef PINEAPPLEMUSIC_MUSICDETAIL_H
#define PINEAPPLEMUSIC_MUSICDETAIL_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class musicDetail; }
QT_END_NAMESPACE

class musicDetail : public QWidget {
Q_OBJECT

public:
    explicit musicDetail(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override; // Set background pic.

    ~musicDetail() override;

private:
    Ui::musicDetail *ui;
};


#endif //PINEAPPLEMUSIC_MUSICDETAIL_H
