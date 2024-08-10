#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initialwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QCryptographicHash>
#include <QDate>
#include <QTime>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->widget_2->setText("智慧园区员工管理系统");

    // 设置字体以支持中文
    QFont font;
    font.setFamily("Microsoft YaHei"); // 使用支持中文的字体
    QApplication::setFont(font);

    connect(&mtimer, &QTimer::timeout, this, &MainWindow::on_time_clicked);
    mtimer.start(1000);

    // 初始显示时间和日期
    on_time_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logButton_clicked()
{
    QString correctUsername = "1996";
    QString correctPassword = "123456";

    QString inputUsername = ui->userEdit->text();
    QString inputPassword = ui->codeEdit->text();
    bool isCheckBoxChecked = ui->checkBox->isChecked();

    if (isCheckBoxChecked && inputUsername == correctUsername && inputPassword == correctPassword)
    {
        qDebug() << "Login successful"; // 添加调试信息
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("登录成功"));
        initialwindow *init = new initialwindow(this);
        init->show();
        this->hide();
    } else {
        qDebug() << "Login failed"; // 添加调试信息
        QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("登录失败"));
    }
}

void MainWindow::on_time_clicked()
{
    QString datestr = QDate::currentDate().toString("yyyy/MM/dd");
    QString timestr = QTime::currentTime().toString("hh:mm:ss");
    qDebug() << "Current date:" << datestr << "Current time:" << timestr;

    if (ui->datalabel && ui->timelabel) {
        ui->datalabel->setText(datestr);
        ui->timelabel->setText(timestr);
    } else {
        qDebug() << "Labels are not initialized or found";
    }
}
