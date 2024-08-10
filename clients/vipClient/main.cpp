#include "mainwindow.h"
#include "user2vip.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    User2vip win;
    win.show();

//    MainWindow w;
//    w.show();
    return a.exec();
}
