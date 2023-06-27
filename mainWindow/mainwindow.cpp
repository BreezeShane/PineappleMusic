#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <iostream>
#include "mainwindow.h"
#include "sidebar/Sidebar.h"
#include "topBar/TopBar.h"
#include "mainContent/MainContent.h"
#include "playBar/PlayBar.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {

    //标题
    this->setWindowTitle("Pineapple Music");
    //主窗口最小大小
    this->setMinimumSize(1200, 800);
    // 获取屏幕的宽度和高度
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    // 计算QWidget的位置，使其居中显示
    int x = (screenWidth - this->width()) / 2;
    int y = (screenHeight - this->height()) / 2 - 50;
    this->move(x, y);

    //主部件
    auto centralwidget = new QWidget(this);
    centralwidget->setMinimumSize(1200, 800);
    centralwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCentralWidget(centralwidget);

    // 主布局---水平布局
    mainLayout = new QHBoxLayout();
    // 子布局---垂直布局
    subLayout = new QVBoxLayout();
    // 侧边栏
    sidebar = new Sidebar();
    // 顶栏
    topBar = new TopBar();
    // 内容显示区域
    mainContent = new MainContent();
    // 播放控制栏
    playBar = new PlayBar();
    // 子布局中加入三个部件
    subLayout->addWidget(topBar);
    subLayout->addWidget(mainContent);
    subLayout->addWidget(playBar);
    // 主布局中加入侧边栏和子布局
    mainLayout->addWidget(sidebar);
    mainLayout->addLayout(subLayout);

    // 主部件加载主布局
    centralwidget->setLayout(mainLayout);


    connect(sidebar->contentLists,  //将显示列表与堆栈窗口关联，点击列表中的按键，显示相应的窗口
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void MainWindow::changePage(QListWidgetItem *current, QListWidgetItem *previous) const {
    if (!current)
        current = previous;
    mainContent->contentPages->setCurrentIndex(sidebar->contentLists->row(current));
}


MainWindow::~MainWindow() = default;

