#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "sidebar/Sidebar.h"
#include "mainContent/MainContent.h"
#include "playBar/PlayBar.h"
#include "model/CloudMusic.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QEvent>
#include <QtGlobal>
#include <QToolBar>
#include "currentPlayList/CurrentPlayList.h"
#include "musicDetail/musicDetail.h"

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    // 主布局---水平布局
    QHBoxLayout *mainLayout{};
    QHBoxLayout *toolLayout{};
    // 子布局---垂直布局
    QVBoxLayout *subLayout{};

    // 侧边栏
    Sidebar *sidebar{};
    // 内容显示区域
    MainContent *mainContent{};
    // 播放控制栏
    PlayBar *playBar{};
    //歌词窗口
    QWidget *widget;

    QToolBar *toolbar{};
    //工具栏按钮
    QPushButton *personalizebt{};
    QPushButton *helpbt{};
    //媒体播放器
    QMediaPlayer *mediaPlayer{};    //播放器
    QVector<QString> currentPlaylistName{};     //当前播放列表
    QVector<QString> currentPlaylist{};     //当前播放列表
    QVector<QString> currentPlaylistLrc{};  //当前播放列表对应的歌词文件列表，没有歌词文件，存储内容为 NoLrc
    QString currentPlayName{};  //当前正在播放的音乐名称
    QString currentPlay{};  //当前正在播放的音乐路径
    QString currentPlayLrc{};   //当前播放音乐的lrc歌词文件路径
    QString durationTime;
    QString positionTime;
    qreal currentSpeed;
    qreal newSpeed;

    musicDetail* detailWindow= nullptr;
    CloudMusic music;
    CurrentPlayList *playList;
    PlayList *playListC;
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setupUI();

    void lyricsUi();

    void retranslateUi();

    //打开侧边栏播放列表
    void openPlayListC();
    // 声明一个枚举类型来表示播放模式
    enum PlayMode {
        SingleLoop, Sequential, Random
    };

    // 声明一个变量来跟踪当前的播放模式
    PlayMode currentPlayMode = Sequential;

    // 声明一个枚举类型来表示歌词状态
    enum LyricsModel {
        yes, no
    };

    // 声明一个变量来跟踪当前的歌词状态
    LyricsModel currenLyricsModel = no;

    ~MainWindow() override;

public slots:

    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

    void startOrPauseMusic();

    void previousMusic();

    void nextMusic();

    void slot_valueChanged_progress(int value);

    void onDurationChanged(qint64 duration);

    void onPositionChanged(qint64 position);

    void togglePlayMode();

    void onSliderPressed();

    void updateCurrentProcessText();

    bool eventFilter(QObject *, QEvent *);

    void setPlaySpeed();

    void lyricsModel();

    void creatLyricsWindow();

    void changeBackground();

    void helpShow();

    //打开播放详情页
    void openDetailWindow();

    //打开播放列表
    void openPlayList();
};

#endif // MAINWINDOW_H
