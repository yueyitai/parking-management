/********************************************************************************
** Form generated from reading UI file 'user2vip.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER2VIP_H
#define UI_USER2VIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_User2vip
{
public:
    QWidget *widget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *province_comboBox;
    QLineEdit *licence_plate_number_lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *owner_name_lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *owner_telephonr_lineEdit;
    QLabel *label_4;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *login_button;
    QPushButton *keyboard_button;
    QPushButton *register_button;

    void setupUi(QWidget *User2vip)
    {
        if (User2vip->objectName().isEmpty())
            User2vip->setObjectName(QStringLiteral("User2vip"));
        User2vip->resize(800, 480);
        User2vip->setStyleSheet(QLatin1String("\n"
"\n"
"QWidget#widget {  \n"
"    background-image: url(:/vip/vip_background.png);  \n"
"}"));
        widget = new QWidget(User2vip);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 801, 481));
        widget->setStyleSheet(QString::fromUtf8("#label_4{\n"
"    font-size: 20px; /* \350\256\276\347\275\256\345\255\227\344\275\223\345\244\247\345\260\217 */  \n"
"    font-weight: bold; /* \350\256\276\347\275\256\345\255\227\344\275\223\345\212\240\347\262\227 */  \n"
"    text-align: center; /* \350\256\276\347\275\256\346\226\207\346\234\254\345\261\205\344\270\255 */  \n"
"}\n"
"\n"
"QLabel{\n"
"	color: white;\n"
"	background-color: rgba(33,33,0,0);\n"
"}\n"
"\n"
"QLineEdit{\n"
"	border: 2px solid #a3a3a3;\n"
"	font: 18pt;\n"
"	border-radius:8px;\n"
"	background-color: white;\n"
"}\n"
"\n"
"QLineEdit::focus{\n"
"	border-color:#488ee7\n"
"}\n"
"\n"
"QLineEdit:hover{\n"
"	border: 2px solid #4e6ef2;\n"
"	font:18pt;\n"
"	border-radius:8px;\n"
"}\n"
"\n"
"QComboBox{\n"
"	background-color: white\n"
"}\n"
"\n"
"#login_button, #register_button{\n"
"font-size: 14px;\n"
"background-color: #e5004f;\n"
"display: inline-block;\n"
"color: #fff;\n"
"text-align: center;\n"
"cursor: pointer;\n"
"float: right;\n"
"}\n"
"\n"
"#keyboard_button{\n"
"font-size: 14px;\n"
""
                        "background-color: #00aa00;\n"
"display: inline-block;\n"
"color: #fff;\n"
"text-align: center;\n"
"cursor: pointer;\n"
"float: right;\n"
"}"));
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(230, 90, 331, 134));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        province_comboBox = new QComboBox(layoutWidget);
        province_comboBox->setObjectName(QStringLiteral("province_comboBox"));
        province_comboBox->setEditable(true);

        horizontalLayout->addWidget(province_comboBox);

        licence_plate_number_lineEdit = new QLineEdit(layoutWidget);
        licence_plate_number_lineEdit->setObjectName(QStringLiteral("licence_plate_number_lineEdit"));

        horizontalLayout->addWidget(licence_plate_number_lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        owner_name_lineEdit = new QLineEdit(layoutWidget);
        owner_name_lineEdit->setObjectName(QStringLiteral("owner_name_lineEdit"));

        horizontalLayout_2->addWidget(owner_name_lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        owner_telephonr_lineEdit = new QLineEdit(layoutWidget);
        owner_telephonr_lineEdit->setObjectName(QStringLiteral("owner_telephonr_lineEdit"));

        horizontalLayout_3->addWidget(owner_telephonr_lineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(300, 40, 281, 31));
        widget1 = new QWidget(widget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(230, 230, 331, 30));
        horizontalLayout_4 = new QHBoxLayout(widget1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        login_button = new QPushButton(widget1);
        login_button->setObjectName(QStringLiteral("login_button"));

        horizontalLayout_4->addWidget(login_button);

        keyboard_button = new QPushButton(widget1);
        keyboard_button->setObjectName(QStringLiteral("keyboard_button"));

        horizontalLayout_4->addWidget(keyboard_button);

        register_button = new QPushButton(widget1);
        register_button->setObjectName(QStringLiteral("register_button"));

        horizontalLayout_4->addWidget(register_button);


        retranslateUi(User2vip);

        QMetaObject::connectSlotsByName(User2vip);
    } // setupUi

    void retranslateUi(QWidget *User2vip)
    {
        User2vip->setWindowTitle(QApplication::translate("User2vip", "Form", 0));
        label->setText(QApplication::translate("User2vip", "\350\275\246\347\211\214\345\217\267\347\240\201\357\274\232", 0));
        province_comboBox->clear();
        province_comboBox->insertItems(0, QStringList()
         << QApplication::translate("User2vip", "\350\265\243", 0)
         << QApplication::translate("User2vip", "\347\262\244", 0)
         << QApplication::translate("User2vip", "\344\272\254", 0)
         << QApplication::translate("User2vip", "\346\264\245", 0)
         << QApplication::translate("User2vip", "\346\262\252", 0)
         << QApplication::translate("User2vip", "\346\270\235", 0)
         << QApplication::translate("User2vip", "\346\241\202", 0)
         << QApplication::translate("User2vip", "\350\222\231", 0)
         << QApplication::translate("User2vip", "\346\226\260", 0)
         << QApplication::translate("User2vip", "\345\256\201", 0)
         << QApplication::translate("User2vip", "\350\227\217", 0)
         << QApplication::translate("User2vip", "\345\206\200", 0)
         << QApplication::translate("User2vip", "\350\261\253", 0)
         << QApplication::translate("User2vip", "\344\272\221", 0)
         << QApplication::translate("User2vip", "\350\276\275", 0)
         << QApplication::translate("User2vip", "\351\273\221", 0)
         << QApplication::translate("User2vip", "\346\271\230", 0)
         << QApplication::translate("User2vip", "\347\232\226", 0)
         << QApplication::translate("User2vip", "\351\262\201", 0)
         << QApplication::translate("User2vip", "\350\213\217", 0)
         << QApplication::translate("User2vip", "\346\265\231", 0)
         << QApplication::translate("User2vip", "\351\204\202", 0)
         << QApplication::translate("User2vip", "\347\224\230", 0)
         << QApplication::translate("User2vip", "\346\231\213", 0)
         << QApplication::translate("User2vip", "\351\231\225", 0)
         << QApplication::translate("User2vip", "\345\220\211", 0)
         << QApplication::translate("User2vip", "\351\227\275", 0)
         << QApplication::translate("User2vip", "\346\241\202", 0)
         << QApplication::translate("User2vip", "\351\235\222", 0)
         << QApplication::translate("User2vip", "\345\267\235", 0)
         << QApplication::translate("User2vip", "\347\220\274", 0)
        );
        label_2->setText(QApplication::translate("User2vip", "\350\275\246\344\270\273\345\247\223\345\220\215\357\274\232", 0));
        label_3->setText(QApplication::translate("User2vip", "\350\275\246\344\270\273\347\224\265\350\257\235\357\274\232", 0));
        label_4->setText(QApplication::translate("User2vip", "\346\254\242\350\277\216\347\224\250\346\210\267\346\263\250\345\206\214\347\231\273\345\275\225", 0));
        login_button->setText(QApplication::translate("User2vip", "\347\231\273\345\275\225", 0));
        keyboard_button->setText(QApplication::translate("User2vip", "\351\224\256\347\233\230", 0));
        register_button->setText(QApplication::translate("User2vip", "\346\263\250\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class User2vip: public Ui_User2vip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER2VIP_H
