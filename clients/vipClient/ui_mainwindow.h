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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *top_frame;
    QLabel *licence_plate_label;
    QCheckBox *checkBox;
    QLabel *label_9;
    QLabel *volitale_money_label;
    QLabel *QR_code_label;
    QPushButton *vip_month_pushbutton;
    QLabel *label_6;
    QLabel *label_5;
    QPushButton *vip_quarter_pushbutton;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *vip_year_pushbutton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_7;
    QPushButton *pushButton;
    QPushButton *payment_button;
    QPushButton *back_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 480);
        MainWindow->setStyleSheet(QLatin1String("#vip_month_pushbutton, #vip_quarter_pushbutton, #vip_year_pushbutton {  \n"
"    border: 1px solid gray;\n"
"	border-radius: 8px;\n"
"}\n"
"\n"
"#vip_year_pushbutton:focus\n"
"{\n"
"	background-color: #ffdddd;\n"
"	border: 2px solid #ff1493;\n"
"}\n"
"\n"
"#vip_quarter_pushbutton:focus{\n"
"	background-color: #ffdddd;\n"
"	border: 2px solid #ff1493;\n"
"}\n"
"#vip_month_pushbutton:focus{\n"
"	background-color: #ffdddd;\n"
"	border: 2px solid #ff1493;\n"
"}\n"
"\n"
"#label_2, #label_4, #label_6\n"
"{\n"
"	font-size: 20px;  \n"
"    font-weight: bold;\n"
"}\n"
"\n"
"#label_7 {  \n"
"    text-decoration: line-through;  \n"
"}\n"
"\n"
"#pushButton{\n"
"	border: 1px solid white;\n"
"	background-color: #ff1493;\n"
"	border-radius: 3px;\n"
"}\n"
"\n"
"#payment_button{\n"
"	border: 1px solid #4e6ef2;\n"
"	border-radius:8px;\n"
"	background-color: rgba(78,110,242,0.5);\n"
"	color:#ffffff;\n"
"}\n"
"\n"
"#back_button{\n"
"	border: 1px solid #4e6ef2;\n"
"	border-radius:8px;\n"
"	background-color: rgba(78,110,242,0.5);\n"
""
                        "	color:#ffffff;\n"
"}\n"
"\n"
"#payment_button:hover{\n"
"	border: 1px solid #4e6ef2;\n"
"	background-color:#4662d9;\n"
"}\n"
"\n"
"#payment_button:pressed{\n"
"	border: 3px solid #000000;\n"
"	background-color: #4e6ef2;\n"
"}\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        top_frame = new QFrame(centralwidget);
        top_frame->setObjectName(QStringLiteral("top_frame"));
        top_frame->setGeometry(QRect(0, 0, 800, 100));
        top_frame->setStyleSheet(QLatin1String("QWidget {  \n"
"    background-image: url(:/vip/starry_sky_background.png);  \n"
"    background-repeat: no-repeat;  \n"
"    background-position: center;  \n"
"}"));
        top_frame->setFrameShape(QFrame::StyledPanel);
        top_frame->setFrameShadow(QFrame::Raised);
        licence_plate_label = new QLabel(top_frame);
        licence_plate_label->setObjectName(QStringLiteral("licence_plate_label"));
        licence_plate_label->setGeometry(QRect(40, 20, 91, 31));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(350, 400, 261, 19));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(420, 350, 291, 31));
        volitale_money_label = new QLabel(centralwidget);
        volitale_money_label->setObjectName(QStringLiteral("volitale_money_label"));
        volitale_money_label->setGeometry(QRect(420, 290, 141, 31));
        QR_code_label = new QLabel(centralwidget);
        QR_code_label->setObjectName(QStringLiteral("QR_code_label"));
        QR_code_label->setGeometry(QRect(280, 270, 100, 100));
        QR_code_label->setStyleSheet(QLatin1String("QLabel {  \n"
"    background-image: url(:/vip/load_QR_code.png);  \n"
"    background-repeat: no-repeat;  \n"
"    background-position: center;  \n"
"}"));
        vip_month_pushbutton = new QPushButton(centralwidget);
        vip_month_pushbutton->setObjectName(QStringLiteral("vip_month_pushbutton"));
        vip_month_pushbutton->setGeometry(QRect(120, 120, 120, 120));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(150, 170, 51, 21));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(140, 135, 81, 31));
        vip_quarter_pushbutton = new QPushButton(centralwidget);
        vip_quarter_pushbutton->setObjectName(QStringLiteral("vip_quarter_pushbutton"));
        vip_quarter_pushbutton->setGeometry(QRect(350, 120, 120, 120));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(370, 135, 91, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(390, 170, 51, 21));
        vip_year_pushbutton = new QPushButton(centralwidget);
        vip_year_pushbutton->setObjectName(QStringLiteral("vip_year_pushbutton"));
        vip_year_pushbutton->setGeometry(QRect(570, 120, 120, 120));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(590, 136, 81, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(600, 170, 61, 21));
        label_2->setMouseTracking(true);
        label_2->setAcceptDrops(false);
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAutoFillBackground(false);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setScaledContents(false);
        label_2->setWordWrap(false);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(610, 200, 61, 21));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(660, 110, 40, 24));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(7);
        pushButton->setFont(font);
        payment_button = new QPushButton(centralwidget);
        payment_button->setObjectName(QStringLiteral("payment_button"));
        payment_button->setGeometry(QRect(600, 310, 93, 28));
        back_button = new QPushButton(centralwidget);
        back_button->setObjectName(QStringLiteral("back_button"));
        back_button->setGeometry(QRect(600, 390, 93, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
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
        licence_plate_label->setText(QString());
        checkBox->setText(QApplication::translate("MainWindow", "\345\220\214\346\204\217\343\200\212vip\346\234\215\345\212\241\345\215\217\350\256\256\343\200\213", 0));
        label_9->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\345\220\214\346\204\217\345\215\217\350\256\256", 0));
        volitale_money_label->setText(QString());
        QR_code_label->setText(QString());
        vip_month_pushbutton->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "\357\277\24525", 0));
        label_5->setText(QApplication::translate("MainWindow", "\346\234\210\345\272\246VIP", 0));
        vip_quarter_pushbutton->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "\345\255\243\345\272\246VIP", 0));
        label_4->setText(QApplication::translate("MainWindow", "\357\277\24568", 0));
        vip_year_pushbutton->setText(QString());
        label->setText(QApplication::translate("MainWindow", "\345\271\264\345\272\246VIP", 0));
        label_2->setText(QApplication::translate("MainWindow", "\357\277\245168", 0));
        label_7->setText(QApplication::translate("MainWindow", "\357\277\245233", 0));
        pushButton->setText(QApplication::translate("MainWindow", "7.2\346\212\230", 0));
        payment_button->setText(QApplication::translate("MainWindow", "\346\224\257\344\273\230\346\210\220\345\212\237", 0));
        back_button->setText(QApplication::translate("MainWindow", "\350\277\224\345\233\236", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
