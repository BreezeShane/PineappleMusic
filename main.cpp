#include "mainWindow/mainwindow.h"

#include "musicDetail/musicDetail.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // 创建应用图标对象
    QIcon icon("../resource/app.png");
    // 设置应用窗口的图标
    app.setWindowIcon(icon);
    MainWindow w;
    w.show();

//    musicDetail s;
//    s.show();
    return app.exec();
}
