/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *vedio_Lb;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *date_Lb;
    QLabel *time_Lb;
    QPushButton *vedio_Bt;
    QPushButton *picture_Bt;
    QLabel *picture_Lb;
    QLabel *car_num_Lb;
    QLabel *fee_Lb;
    QLineEdit *fee_Ed;
    QPushButton *change_Bt;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 480);
        MainWindow->setStyleSheet(QLatin1String("QLabel#vedio_Lb\n"
"{\n"
"	background-color:#0000F0;\n"
"}\n"
"QLabel#picture_Lb\n"
"{\n"
"	background-color:#F0F000;\n"
"}\n"
"QLabel#date_Lb\n"
"{\n"
"	background-color:#FFFF00;\n"
"}\n"
"QLabel#time_Lb\n"
"{\n"
"	background-color:#FFFF00;\n"
"}\n"
"QLabel#car_num_Lb\n"
"{\n"
"	background-color:#FF9FF0;\n"
"}\n"
"QLabel#fee_Lb\n"
"{\n"
"	background-color:#1F9FF0;\n"
"}\n"
"QLabel#show_Lb\n"
"{\n"
"	background-color:#1F9990;\n"
"\n"
"	color:rgba(200,100,100,0.5);\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        vedio_Lb = new QLabel(centralwidget);
        vedio_Lb->setObjectName(QStringLiteral("vedio_Lb"));
        vedio_Lb->setGeometry(QRect(0, -10, 640, 480));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(640, 0, 171, 441));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        date_Lb = new QLabel(widget);
        date_Lb->setObjectName(QStringLiteral("date_Lb"));

        verticalLayout->addWidget(date_Lb);

        time_Lb = new QLabel(widget);
        time_Lb->setObjectName(QStringLiteral("time_Lb"));

        verticalLayout->addWidget(time_Lb);

        vedio_Bt = new QPushButton(widget);
        vedio_Bt->setObjectName(QStringLiteral("vedio_Bt"));

        verticalLayout->addWidget(vedio_Bt);

        picture_Bt = new QPushButton(widget);
        picture_Bt->setObjectName(QStringLiteral("picture_Bt"));

        verticalLayout->addWidget(picture_Bt);

        picture_Lb = new QLabel(widget);
        picture_Lb->setObjectName(QStringLiteral("picture_Lb"));

        verticalLayout->addWidget(picture_Lb);

        car_num_Lb = new QLabel(widget);
        car_num_Lb->setObjectName(QStringLiteral("car_num_Lb"));

        verticalLayout->addWidget(car_num_Lb);

        fee_Lb = new QLabel(widget);
        fee_Lb->setObjectName(QStringLiteral("fee_Lb"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(6);
        fee_Lb->setFont(font);

        verticalLayout->addWidget(fee_Lb);

        fee_Ed = new QLineEdit(widget);
        fee_Ed->setObjectName(QStringLiteral("fee_Ed"));

        verticalLayout->addWidget(fee_Ed);

        change_Bt = new QPushButton(widget);
        change_Bt->setObjectName(QStringLiteral("change_Bt"));

        verticalLayout->addWidget(change_Bt);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        vedio_Lb->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        date_Lb->setText(QApplication::translate("MainWindow", "0000-00-00", 0));
        time_Lb->setText(QApplication::translate("MainWindow", "00:00:00", 0));
        vedio_Bt->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\346\221\204\345\203\217\345\244\264", 0));
        picture_Bt->setText(QApplication::translate("MainWindow", "\346\213\215\347\205\247", 0));
        picture_Lb->setText(QApplication::translate("MainWindow", "\347\205\247\347\211\207", 0));
        car_num_Lb->setText(QApplication::translate("MainWindow", "\350\275\246\347\211\214\345\217\267", 0));
        fee_Lb->setText(QApplication::translate("MainWindow", "\346\257\217\345\215\212\344\270\252\345\260\217\346\227\266\346\224\266\350\264\271\351\222\261\346\225\260(\345\215\212\345\260\217\346\227\266\345\206\205\344\270\215\346\224\266\350\264\271\357\274\211", 0));
        change_Bt->setText(QApplication::translate("MainWindow", "\346\233\264\346\224\271\351\222\261\346\225\260", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
