//
// Created by juncheng on 2023/7/6.
//

#ifndef PINEAPPLEMUSIC_LYRICWIDGET_H
#define PINEAPPLEMUSIC_LYRICWIDGET_H


#include <QLabel>

class LyricWidget : public QLabel
{
    Q_OBJECT

public:
    explicit LyricWidget(QWidget *parent = nullptr);

    void setLyricFile(const QString &fileName);
    void setCurrentTime(qint64 time);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<qint64, QString> m_lyrics;
    int m_currentIndex;
};


#endif //PINEAPPLEMUSIC_LYRICWIDGET_H
