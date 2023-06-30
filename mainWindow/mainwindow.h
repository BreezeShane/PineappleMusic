#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "sidebar/Sidebar.h"
#include "mainContent/MainContent.h"
#include "playBar/PlayBar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 主布局---水平布局
    QHBoxLayout *mainLayout;
    // 子布局---垂直布局
    QVBoxLayout *subLayout ;
    // 侧边栏
    Sidebar *sidebar;
    // 内容显示区域
    MainContent *mainContent;
    // 播放控制栏
    PlayBar *playBar;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous) const;

};
#endif // MAINWINDOW_H
