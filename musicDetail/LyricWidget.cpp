//
// Created by juncheng on 2023/7/6.
//

#include <QFile>
#include <QPainter>
#include <QTextStream>
#include "LyricWidget.h"

LyricWidget::LyricWidget(QWidget *parent)
        : QLabel(parent)
        , m_currentIndex(0)
{
    this->setAlignment(Qt::AlignCenter);
    this->setFont(QFont("Microsoft YaHei", 16));
    this->setStyleSheet("color: white;");
}

void LyricWidget::setLyricFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    m_lyrics.clear();
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QRegExp rx("\\[(\\d+):(\\d+\\.\\d+)\\](.*)");
        if (rx.indexIn(line) != -1) {
            qint64 time = rx.cap(1).toInt() * 60 * 1000 + rx.cap(2).toDouble() * 1000;
            QString text = rx.cap(3);
            m_lyrics.insert(time, text);
        }
    }

    file.close();
}

void LyricWidget::setCurrentTime(qint64 time)
{
    int index = 0;
    for (auto it = m_lyrics.constBegin(); it != m_lyrics.constEnd(); ++it) {
        if (it.key() <= time) {
            index = it.key();
        } else {
            break;
        }
    }

    if (index != m_currentIndex) {
        m_currentIndex = index;
        update();
    }
}

void LyricWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QFontMetrics metrics(font());
    int lineHeight = metrics.lineSpacing();
    int y = height() / 2 - (m_lyrics.size() / 2) * lineHeight;

    for (auto it = m_lyrics.constBegin(); it != m_lyrics.constEnd(); ++it) {
        if (it.key() == m_currentIndex) {
            painter.setPen(Qt::red);
        } else {
            painter.setPen(Qt::white);
        }

        QString line = it.value();
        int lineWidth = metrics.horizontalAdvance(line);
        int x = (width() - lineWidth) / 2;

        painter.drawText(x, y, line);
        y += lineHeight;
    }
}