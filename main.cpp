#include "mainWindow/mainwindow.h"

#include "musicDetail/musicDetail.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QIcon icon(":/resource/app.png");
    app.setWindowIcon(icon);
    MainWindow w;
    w.show();

//    musicDetail s;
//    s.show();
    return app.exec();
}
