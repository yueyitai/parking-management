/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *title;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *time;
    QLabel *data;
    QLabel *weather;
    QLabel *num;
    QLabel *other;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 480);
        Widget->setMinimumSize(QSize(0, 0));
        Widget->setMaximumSize(QSize(16777215, 16777215));
        Widget->setStyleSheet(QLatin1String("QLabel{\n"
"	background-color: rgba(51, 194, 255,0.3);\n"
"	border:1px solid rgb(0, 0, 0);\n"
"	border-radius:8px;\n"
"}\n"
"QLabel#num{\n"
"	\n"
"	border-image: url(:/other/wei.jpg);\n"
"}"));
        gridLayout = new QGridLayout(Widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        title = new QLabel(Widget);
        title->setObjectName(QStringLiteral("title"));
        QFont font;
        font.setPointSize(12);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(title);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        time = new QLabel(Widget);
        time->setObjectName(QStringLiteral("time"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        time->setFont(font1);
        time->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(time);

        data = new QLabel(Widget);
        data->setObjectName(QStringLiteral("data"));
        data->setFont(font1);
        data->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(data);

        weather = new QLabel(Widget);
        weather->setObjectName(QStringLiteral("weather"));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(true);
        font2.setWeight(75);
        weather->setFont(font2);
        weather->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(weather);

        num = new QLabel(Widget);
        num->setObjectName(QStringLiteral("num"));
        num->setFont(font1);
        num->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(num);

        other = new QLabel(Widget);
        other->setObjectName(QStringLiteral("other"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(other->sizePolicy().hasHeightForWidth());
        other->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(other);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 4);
        verticalLayout->setStretch(4, 4);

        horizontalLayout->addLayout(verticalLayout);

        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(label);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 4);

        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 9);

        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        title->setText(QApplication::translate("Widget", "XXX\345\201\234\350\275\246\345\234\272\346\254\242\350\277\216\346\202\250\347\232\204\345\205\211\344\270\264    \345\271\277\345\221\212\346\212\225\346\224\276\350\201\224\347\263\273\347\224\265\350\257\235\357\274\23215191793270", 0));
        time->setText(QApplication::translate("Widget", "00:00:00", 0));
        data->setText(QApplication::translate("Widget", "yyyy-mm-dd", 0));
        weather->setText(QApplication::translate("Widget", "\346\267\273\345\212\240\345\245\275\345\217\213\350\257\267\346\211\253\347\240\201\357\274\232", 0));
        num->setText(QString());
        other->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
