#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "EClient.h"
#include <QPixmap>
#include <QApplication>
#include <QLabel>
#include <QDebug>
#include <QDir>
#include <QFont>
#include <QDateTime>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_plate(QString data)
{
    ui->licence_plate_label->setText(data);

}


void MainWindow::on_checkBox_clicked(bool checked)
{
    QPixmap pixmap1("money_receving_QR_code.jpg");
    QPixmap pixmap2("load_QR_code.png");
    if(checked){
        ui->label_9->setText("请使用微信或支付宝扫码支付");
        ui->QR_code_label->setPixmap(pixmap1);
        ui->QR_code_label->show();
        ui->volitale_money_label->setText(" ");
    }else{
        ui->label_9->setText("请先同意协议");
        ui->QR_code_label->setPixmap(pixmap2);
        ui->QR_code_label->show();
        ui->volitale_money_label->setText(" ");
    }
}

void MainWindow::on_vip_month_pushbutton_clicked()
{
    QFont font;
    font.setPointSize(20);
    font.setWeight(QFont::Bold);
    ui->volitale_money_label->setFont(font);
    ui->volitale_money_label->setText(ui->label_6->text());

}

void MainWindow::on_vip_quarter_pushbutton_clicked()
{
    QFont font;
    font.setPointSize(20);
    font.setWeight(QFont::Bold);
    ui->volitale_money_label->setFont(font);
    ui->volitale_money_label->setText(ui->label_4->text());
}

void MainWindow::on_vip_year_pushbutton_clicked()
{
    QFont font;
    font.setPointSize(20);
    font.setWeight(QFont::Bold);
    ui->volitale_money_label->setFont(font);
    ui->volitale_money_label->setText(ui->label_2->text());
}

void MainWindow::on_payment_button_clicked()
{
    //获取当前的日期和时间
//    QDateTime current_time = QDateTime::currentDateTime();
//    qDebug()<<"当前时间:"<<current_time.toString("yyyy-MM-dd HH:mm:ss");
//    QString select_money = ui->volitale_money_label->text();
//    if(select_money == "￥25"){
//        QDateTime one_month_later = current_time.addMonths(1);
//        qDebug()<<"一个月后:"<<one_month_later.toString("yyyy-MM-dd HH:mm:ss");
//    }else if(select_money == "￥68"){
//        QDateTime three_month_later = current_time.addMonths(3);
//        qDebug()<<"一个季度后:"<<three_month_later.toString("yyyy-MM-dd HH:mm:ss");
//    }else if(select_money == "￥168"){
//        QDateTime one_year_later = current_time.addMonths(12);
//        qDebug()<<"一年后:"<<one_year_later.toString("yyyy-MM-dd HH:mm:ss");
//    }
    //此时用户已经支付完成，发送一个请求，修改改车牌的start_time和
    //end_time
    QDateTime current_time = QDateTime::currentDateTime();
    QString currentTime = current_time.toString("yyyy-MM-dd");

    QString select_money = ui->volitale_money_label->text();
    QString time;
    if(select_money == "￥25"){
        QDateTime one_month_later = current_time.addMonths(1);
        time = one_month_later.toString("yyyy-MM-dd");
    }else if(select_money == "￥68"){
        QDateTime three_month_later = current_time.addMonths(3);
        time = three_month_later.toString("yyyy-MM-dd");
    }else if(select_money == "￥168"){
        QDateTime one_year_later = current_time.addMonths(12);
        time = one_year_later.toString("yyyy-MM-dd");
    }
    EClient ec;
    QString recv;
    //创建一个json
    QJsonObject j;
    j["start_time"] = currentTime;
    j["end_time"] = time;
    j["licence_plate"] = ui->licence_plate_label->text();
    QJsonDocument jsonDoc(j);
    //发送请求
    ec.operateDatabase(EClient::VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE, &recv, jsonDoc.toJson());

    if(recv == "SUCCESS"){
        QMessageBox::warning(this, "成功", "支付成功!");

    }else{
        QMessageBox::warning(this, "错误", "支付失败");

    }


}

void MainWindow::on_back_button_clicked()
{
    this->parentWidget()->show();
    delete this;
}
