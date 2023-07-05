#include "mainWindow/mainwindow.h"

#include "musicDetail/musicDetail.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // ����Ӧ��ͼ�����
    QIcon icon("../resource/app.png");
    // ����Ӧ�ô��ڵ�ͼ��
    app.setWindowIcon(icon);
    MainWindow w;
    w.show();

//    musicDetail s;
//    s.show();
    return app.exec();
}
