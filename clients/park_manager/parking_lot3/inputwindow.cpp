#include "inputwindow.h"
#include "ui_inputwindow.h"

InputWindow::InputWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputWindow)
{
    ui->setupUi(this);
}

InputWindow::~InputWindow()
{
    delete ui;
}

void InputWindow::on_ok_Bt_clicked()
{
    //通过信号把数据发送出去
    emit sendData(ui->fee_Ed->text());
    //显示第二个窗口，销毁本窗口
    this->parentWidget()->show();
    this->deleteLater();
}
