#include "addwindow.h"
#include "EClient.h"
#include "ui_addwindow.h"
#include<QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

addwindow::addwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addwindow)
{
    ui->setupUi(this);
    ui->widgetRoll->setText("智慧园区员工管理系统");

}

addwindow::~addwindow()
{
    delete ui;
}

void addwindow::on_backButton_clicked()
{
    if (this->parentWidget())
    {
        this->parentWidget()->show();
    }
    delete  this; // 或者使用 hide();
}

void addwindow::on_addAllButton_clicked()
{
    int state = 0;
    if(ui->addStateEdit->text() == "在职") state = 1;
    else if (ui->addStateEdit->text() == "离职") state = 0;

    //创建一个json对象
    QJsonObject jsonObject;
    //获取文本框信息
    jsonObject["name"]          = ui->addNameEdit->text();
    jsonObject["gender"]        = ui->addGenderEdit->text();
    jsonObject["age"]           = ui->addAgeEdit->text().toInt();
    jsonObject["hir_time"]      = ui->addTimeEdit->text();
    jsonObject["state"]         = state;
    jsonObject["res_time"]      = ui->addQuitTimeEdit->text();
    jsonObject["phone"]         = ui->addCallEdit->text();
    jsonObject["licence_plate"] = ui->addCarEdit->text();
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);
    QString jsonString = QString::fromUtf8(jsonData);
    qDebug().noquote()<<"JSON String"<<jsonString;
    qDebug()<<"JSON String"<<jsonData;

    EClient client;

    QString recvBuf;
    if(!client.operateDatabase(EClient::ECLIENT_INSERT_ONE_INFO,nullptr, jsonString))
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("添加失败"));
    }
    else{
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("添加成功"));

    }
    qDebug().noquote() << "Received Buffer:" << recvBuf;


}

void addwindow::on_addAllButton_2_clicked()
{

    ui->addNameEdit->clear();
    ui->addGenderEdit->clear();
    ui->addAgeEdit->clear();
    ui->addTimeEdit->clear();
    ui->addStateEdit->clear();
    ui->addQuitTimeEdit->clear();
    ui->addCallEdit->clear();
    ui->addCarEdit->clear();
}
