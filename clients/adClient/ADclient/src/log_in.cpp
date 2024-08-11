#include "inc/log_in.h"
#include "ui_log_in.h"
#include "inc/mainwindow.h"

#include <QDebug>
#include <QMessageBox>

log_in::log_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::log_in)
{
    ui->setupUi(this);
}

log_in::~log_in()
{
    delete ui;
}

void log_in::on_login_clicked()
{
    if(ui->id->text() == "root" && ui->password->text() == "123456")
    {
        this->close();
        MainWindow *w = new MainWindow(this);
        w->show();
    }
    else{
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("账号或密码错误！"));
        ui->id->setText("");
        ui->password->setText("");
    }

}
