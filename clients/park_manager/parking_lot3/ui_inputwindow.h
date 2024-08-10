/********************************************************************************
** Form generated from reading UI file 'inputwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTWINDOW_H
#define UI_INPUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <keybutton.h>

QT_BEGIN_NAMESPACE

class Ui_InputWindow
{
public:
    QWidget *centralwidget;
    QLabel *fee_Lb;
    QLineEdit *fee_Ed;
    QWidget *widget;
    QGridLayout *gridLayout;
    KeyButton *toolButton;
    KeyButton *toolButton_2;
    KeyButton *toolButton_3;
    KeyButton *toolButton_6;
    KeyButton *toolButton_5;
    KeyButton *toolButton_4;
    KeyButton *toolButton_9;
    KeyButton *toolButton_8;
    KeyButton *toolButton_7;
    KeyButton *toolButton_10;
    KeyButton *toolButton_12;
    QPushButton *ok_Bt;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *InputWindow)
    {
        if (InputWindow->objectName().isEmpty())
            InputWindow->setObjectName(QStringLiteral("InputWindow"));
        InputWindow->resize(800, 600);
        InputWindow->setStyleSheet(QLatin1String("QLabel#fee_Lb\n"
"{\n"
"	background-color:#1F9FF0;\n"
"}"));
        centralwidget = new QWidget(InputWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        fee_Lb = new QLabel(centralwidget);
        fee_Lb->setObjectName(QStringLiteral("fee_Lb"));
        fee_Lb->setGeometry(QRect(230, 90, 281, 51));
        fee_Ed = new QLineEdit(centralwidget);
        fee_Ed->setObjectName(QStringLiteral("fee_Ed"));
        fee_Ed->setGeometry(QRect(230, 150, 281, 31));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(230, 210, 281, 211));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        toolButton = new KeyButton(widget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton, 0, 0, 1, 1);

        toolButton_2 = new KeyButton(widget);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        sizePolicy.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_2, 0, 1, 1, 1);

        toolButton_3 = new KeyButton(widget);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        sizePolicy.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_3, 0, 2, 1, 1);

        toolButton_6 = new KeyButton(widget);
        toolButton_6->setObjectName(QStringLiteral("toolButton_6"));
        sizePolicy.setHeightForWidth(toolButton_6->sizePolicy().hasHeightForWidth());
        toolButton_6->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_6, 1, 0, 1, 1);

        toolButton_5 = new KeyButton(widget);
        toolButton_5->setObjectName(QStringLiteral("toolButton_5"));
        sizePolicy.setHeightForWidth(toolButton_5->sizePolicy().hasHeightForWidth());
        toolButton_5->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_5, 1, 1, 1, 1);

        toolButton_4 = new KeyButton(widget);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        sizePolicy.setHeightForWidth(toolButton_4->sizePolicy().hasHeightForWidth());
        toolButton_4->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_4, 1, 2, 1, 1);

        toolButton_9 = new KeyButton(widget);
        toolButton_9->setObjectName(QStringLiteral("toolButton_9"));
        sizePolicy.setHeightForWidth(toolButton_9->sizePolicy().hasHeightForWidth());
        toolButton_9->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_9, 2, 0, 1, 1);

        toolButton_8 = new KeyButton(widget);
        toolButton_8->setObjectName(QStringLiteral("toolButton_8"));
        sizePolicy.setHeightForWidth(toolButton_8->sizePolicy().hasHeightForWidth());
        toolButton_8->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_8, 2, 1, 1, 1);

        toolButton_7 = new KeyButton(widget);
        toolButton_7->setObjectName(QStringLiteral("toolButton_7"));
        sizePolicy.setHeightForWidth(toolButton_7->sizePolicy().hasHeightForWidth());
        toolButton_7->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_7, 2, 2, 1, 1);

        toolButton_10 = new KeyButton(widget);
        toolButton_10->setObjectName(QStringLiteral("toolButton_10"));
        sizePolicy.setHeightForWidth(toolButton_10->sizePolicy().hasHeightForWidth());
        toolButton_10->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_10, 3, 0, 1, 1);

        toolButton_12 = new KeyButton(widget);
        toolButton_12->setObjectName(QStringLiteral("toolButton_12"));
        sizePolicy.setHeightForWidth(toolButton_12->sizePolicy().hasHeightForWidth());
        toolButton_12->setSizePolicy(sizePolicy);

        gridLayout->addWidget(toolButton_12, 3, 1, 1, 1);

        ok_Bt = new QPushButton(widget);
        ok_Bt->setObjectName(QStringLiteral("ok_Bt"));
        sizePolicy.setHeightForWidth(ok_Bt->sizePolicy().hasHeightForWidth());
        ok_Bt->setSizePolicy(sizePolicy);

        gridLayout->addWidget(ok_Bt, 3, 2, 1, 1);

        InputWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(InputWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        InputWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(InputWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        InputWindow->setStatusBar(statusbar);

        retranslateUi(InputWindow);

        QMetaObject::connectSlotsByName(InputWindow);
    } // setupUi

    void retranslateUi(QMainWindow *InputWindow)
    {
        InputWindow->setWindowTitle(QApplication::translate("InputWindow", "MainWindow", 0));
        fee_Lb->setText(QApplication::translate("InputWindow", "\350\257\267\350\276\223\345\205\245\345\201\234\350\275\246\350\264\271", 0));
        toolButton->setText(QApplication::translate("InputWindow", "7", 0));
        toolButton_2->setText(QApplication::translate("InputWindow", "8", 0));
        toolButton_3->setText(QApplication::translate("InputWindow", "9", 0));
        toolButton_6->setText(QApplication::translate("InputWindow", "4", 0));
        toolButton_5->setText(QApplication::translate("InputWindow", "5", 0));
        toolButton_4->setText(QApplication::translate("InputWindow", "6", 0));
        toolButton_9->setText(QApplication::translate("InputWindow", "1", 0));
        toolButton_8->setText(QApplication::translate("InputWindow", "2", 0));
        toolButton_7->setText(QApplication::translate("InputWindow", "3", 0));
        toolButton_10->setText(QApplication::translate("InputWindow", "0", 0));
        toolButton_12->setText(QApplication::translate("InputWindow", ".", 0));
        ok_Bt->setText(QApplication::translate("InputWindow", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class InputWindow: public Ui_InputWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTWINDOW_H
