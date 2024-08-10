#include "alterwindow.h"
#include "ui_alterwindow.h"
#include "EClient.h"
#include <QJsonObject>
#include <QMessageBox>
#include <QMovie>
alterwindow::alterwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::alterwindow)
{
    ui->setupUi(this);
    ui->widgetFind->setText("智慧园区员工管理系统");

}

alterwindow::~alterwindow()
{
    delete ui;
}

void alterwindow::on_backButton3_clicked()
{
    if (this->parentWidget()) {
            this->parentWidget()->show();
        }
    delete  this; // 或者使用 hide();
}

void alterwindow::on_alterFindButton_clicked()
{
    EClient client;
    QJsonObject jsonObject;
    //获取文本框信息
    jsonObject["id"]          = ui->alterIdEdit->text().toInt();
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);
    QString jsonString = QString::fromUtf8(jsonData);
    qDebug().noquote()<<"JSON String"<<jsonString;
    QString recvbuf;
    client.operateDatabase(EClient::ECLIENT_QUERY_ONE_INFO_BY_ID,&recvbuf,jsonString);
    // 打印返回的 JSON 数据
    qDebug().noquote() << "Received JSON:" << recvbuf;

    // 解析返回的 JSON 数据
    QJsonDocument doc = QJsonDocument::fromJson(recvbuf.toUtf8());
    QJsonObject alterjson = doc.object(); // 假设返回的是一个 JSON 对象

    ui->alterNameEdit->setText(alterjson["name"].toString());
    ui->alterGenderEdit->setText(alterjson["gender"].toString());
    ui->alterAgeEdit->setText(QString::number(alterjson["age"].toInt()));
    ui->alterInTimeEdit->setText(alterjson["hir_time"].toString());
    ui->alterStateTimeEdit->setText(alterjson["state"].toBool() ? "在职" : "离职");
    ui->alterQuitTimeEdit->setText(alterjson["res_time"].toString());
    ui->alterCallEdit->setText(alterjson["phone"].toString());
    ui->alterCarEdit->setText(alterjson["licence_plate"].toString());

}

void alterwindow::on_alterAllButton_clicked()
{
    //创建一个json对象
    QJsonObject jsonObject;
    //获取文本框信息
    jsonObject["id"]            = ui->alterIdEdit->text();
    jsonObject["name"]          = ui->alterNameEdit->text();
    jsonObject["gender"]        = ui->alterGenderEdit->text();
    jsonObject["age"]           = ui->alterAgeEdit->text();
    jsonObject["hir_time"]      = ui->alterInTimeEdit->text();
    jsonObject["state"]         = ui->alterStateTimeEdit->text();
    jsonObject["res_time"]      = ui->alterQuitTimeEdit->text();
    jsonObject["phone"]         = ui->alterCallEdit->text();
    jsonObject["licence_plate"] = ui->alterCarEdit->text();
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);
    QString jsonString = QString::fromUtf8(jsonData);
    qDebug().noquote()<<"JSON String"<<jsonString;
    EClient client;
    QString recvBuf;
    if(!client.operateDatabase(EClient::ECLIENT_UPDATE_ONE_INFO_BY_ID,nullptr,jsonString))
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("修改失败"));
    }
    else{
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("修改成功"));

    }
    qDebug().noquote() << "Received Buffer:" << recvBuf;


}
