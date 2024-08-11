#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    if(QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
      QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);
    QApplication a(argc, argv);

    Widget w;
    w.showFullScreen();   //全屏显示
    w.show();

    return a.exec();
}
