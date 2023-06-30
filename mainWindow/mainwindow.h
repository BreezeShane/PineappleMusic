#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "sidebar/Sidebar.h"
#include "mainContent/MainContent.h"
#include "playBar/PlayBar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMediaPlayer>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    // 主布局---水平布局
    QHBoxLayout *mainLayout{};
    // 子布局---垂直布局
    QVBoxLayout *subLayout{};
    // 侧边栏
    Sidebar *sidebar{};
    // 内容显示区域
    MainContent *mainContent{};
    // 播放控制栏
    PlayBar *playBar{};
    //媒体播放器
    QMediaPlayer *mediaPlayer{};
    QVector<QString> currentPlaylist{};
    QString currentPlay{};
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setupUI();

    void retranslateUi();

    QMediaPlayer *getMediaPlayer() const;

    const QVector<QString> &getCurrentPlaylist() const;

    void setCurrentPlaylist(const QVector<QString> &playlist);

    const QString &getCurrentPlay() const;

    void setCurrentPlay(const QString &musicPath);

    ~MainWindow() override;

public slots:

    void changePage(QListWidgetItem *current, QListWidgetItem *previous) const;
    void startOrPauseMusic();
};

#endif // MAINWINDOW_H
