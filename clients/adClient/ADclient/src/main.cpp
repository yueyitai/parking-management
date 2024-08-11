#include "inc/mainwindow.h"
#include "inc/log_in.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
      QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);

    QApplication a(argc, argv);
    log_in log;
//    MainWindow w;
//    w.show();
    log.show();

    return a.exec();
}
