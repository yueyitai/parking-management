#include "inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "inc/alter.h"
#include "inc/look.h"
#include "inc/dele.h"
#include "inc/add.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <inc/mainwindow.h>

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

//打开添加窗口
void MainWindow::on_addBt_clicked()
{
    add *win = new add(this);
    this->hide();
    win->show();
}

//打开删除窗口
void MainWindow::on_deleteBt_clicked()
{
    dele *win = new dele(this);
    this->hide();
    win->show();
}

//打开修改窗口
void MainWindow::on_alterBt_clicked()
{
    alter *win =new alter(this);
    this->hide();
    win->show();
}

//打开查看窗口
void MainWindow::on_lookBt_clicked()
{
    look *win =new look(this);
    this->hide();
    //第三个界面在返回的时候会发送一个sendData信号，定义一个槽函数关联这个信号
    connect(win, &look::sendData,this, &MainWindow::recvData);
    win->show();
}

void MainWindow::recvData(QString data)
{
    qDebug()<< "接受的信息";
    qDebug()<< data;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = jsonDoc.object();

    QString itemId = QString("%1").arg(obj["id"].toInt());
    QString itemName = obj["name"].toString();
    QString itemPhone = obj["phone"].toString();
    QString itemStartDate = obj["start_date"].toString();
    QString itemExpireDate = obj["expirat_date"].toString(); // 注意：这里应该是"expire_date"而不是"expirat_date"


    ui->name->setText(itemName);
    ui->stime->setText(itemStartDate);
    ui->otime->setText(itemExpireDate);
    ui->photo->setText(itemPhone);
}

//void MainWindow::recvLookData(QString data)
//{
//    qDebug()<< "接受的信息";
//    qDebug()<< data;
//    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
//    QJsonObject obj = jsonDoc.object();

//    QString itemId = QString("%1").arg(obj["id"].toInt());
//    QString itemName = obj["name"].toString();
//    QString itemPhone = obj["phone"].toString();
//    QString itemStartDate = obj["start_date"].toString();
//    QString itemExpireDate = obj["expirat_date"].toString(); // 注意：这里应该是"expire_date"而不是"expirat_date"


//    ui->name->setText(itemName);
//    ui->stime->setText(itemStartDate);
//    ui->otime->setText(itemExpireDate);
//    ui->photo->setText(itemPhone);
////    QString listItem = QString("Id: %1\t Name: %2\t Phone: %3\t Start Date: %4\t Expire Date: %5")
////        .arg(itemId, itemName, itemPhone, itemStartDate, itemExpireDate);
////    ui->listWidget->addItem(listItem);
//}
