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
#include <QEvent>
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
    QMediaPlayer *mediaPlayer{};    //播放器
    QVector<QString> currentPlaylist{};     //当前播放列表
    QVector<QString> currentPlaylistLrc{};  //当前播放列表对应的歌词文件列表，没有歌词文件，存储内容为 NoLrc
    QString currentPlay{};  //当前正在播放的音乐路径
    QString currentPlayLrc{};   //当前播放音乐的lrc歌词文件路径
    QString durationTime;
    QString positionTime;
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setupUI();

    void retranslateUi();


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
    void togglePlayMode();
    void onSliderPressed();
    void updateCurrentProcessText();
    bool eventFilter(QObject* , QEvent*);
};

#endif // MAINWINDOW_H
