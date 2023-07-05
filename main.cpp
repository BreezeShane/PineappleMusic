#include "mainWindow/mainwindow.h"

#include "musicDetail/musicDetail.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
//    musicDetail s;
//    s.show();
    return app.exec();
}
