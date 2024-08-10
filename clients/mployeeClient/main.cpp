#include "mainwindow.h"
#include "addwindow.h"
#include <QApplication>
#include <QLabel>
#include "initialwindow.h"
#include "findwindow.h"
#include "alterwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "EClient.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *w = new MainWindow();
    w->show();

    return a.exec();
}
