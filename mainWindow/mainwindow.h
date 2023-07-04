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
    QString durationTime;
    QString positionTime;
    bool isSliderPressed;
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setupUI();

    void retranslateUi();

    QMediaPlayer *getMediaPlayer() const;

    const QVector<QString> &getCurrentPlaylist() const;

    void setCurrentPlaylist(const QVector<QString> &playlist);

    const QString &getCurrentPlay() const;

    void setCurrentPlay(const QString &musicPath);

    // 声明一个枚举类型来表示播放模式
    enum PlayMode { SingleLoop, Sequential, Random };

    // 声明一个变量来跟踪当前的播放模式
    PlayMode currentPlayMode = Sequential;

    ~MainWindow() override;

public slots:

    void changePage(QListWidgetItem *current, QListWidgetItem *previous) const;
    void startOrPauseMusic();
    void previousMusic();
    void nextMusic();
    void slot_valueChanged_progress(int value);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onSliderPressed(qint64,int);
    void togglePlayMode();
};

#endif // MAINWINDOW_H
