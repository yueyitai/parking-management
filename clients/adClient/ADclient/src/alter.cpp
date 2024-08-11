#include "inc/alter.h"
#include "inc/alter1.h"
#include "ui_alter.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include <inc/EClient.h>

QString alterBuff;

bool alterTem;
alter::alter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::alter)
{
    ui->setupUi(this);

    EClient alterCli;
    alterTem = alterCli.operateDatabase(EClient::ADCLIENT_GET_ALL_INFO,&alterBuff,nullptr);
    if(alterTem)
    {
        QMessageBox::information(this, "提示", "查询成功");

//        qDebug() << "修改查询的全部数据";
//        qDebug() << alterBuff;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(alterBuff.toUtf8());
        QJsonArray jsonArray = jsonDoc.array();

        for (auto item : jsonArray)
        {
            QJsonObject obj = item.toObject();
            //QString::number(alterjson["age"].toInt())
            QString itemId = QString("%1").arg(obj["id"].toInt());
            QString itemName = obj["name"].toString();
            QString itemPhone = obj["phone"].toString();
            QString itemStartDate = obj["start_date"].toString();
            QString itemExpireDate = obj["expirat_date"].toString(); // 注意：这里应该是"expire_date"而不是"expirat_date"

            QString listItem = QString("序号: %1\t 投递单位: %2\t 联系电话: %3\t 投放日期: %4\t 失效日期: %5")
                .arg(itemId, itemName, itemPhone, itemStartDate, itemExpireDate);
            ui->listWidget->addItem(listItem);
        }
    }
    else
    {
        QMessageBox::information(this, "提示", "查询失败");
    }
}

alter::~alter()
{
    delete ui;
}

void alter::on_alterEnt_clicked()
{
    if(ui->alterId->text() == "")
    {
        QMessageBox::information(this, "提示", "请正确输入需要操作的ID");
    }
    else
    {
        QString buf = ui->alterId->text();
        QJsonObject image;
        image.insert("id",buf.toInt());
        //把json数据转换为字符串
        QJsonDocument doc;
        doc.setObject(image);
        QString sentBuff;
        sentBuff = doc.toJson();  //转字符串

        EClient alterCli;
        alterTem = alterCli.operateDatabase(EClient::ADCLIENT_QUERY_ONE_INFO_BY_ID,&alterBuff,sentBuff);
        if(alterTem)
        {
            alter1 *win = new alter1(this);
            //第三个界面在返回的时候会发送一个sendData信号，定义一个槽函数关联这个信号
            connect(win, &alter1::sendAlterData,this, &alter::recvAlter1Data);

            win->receiveAlterData(alterBuff);

            win->show();

//            qDebug() << "查询的单条信息";
//            qDebug() << alterBuff;
            }
            else
            {
                QMessageBox::information(this, "提示", "查询失败");
            }



    }
}

void alter::on_alterBreak_clicked()
{
    //返回上一级窗口
    this->parentWidget()->show();
    delete this;//释放本窗口（第三个窗口）
}

void alter::recvAlter1Data(QString data)
{
    ui->listWidget->clear();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonArray jsonArray = jsonDoc.array();

    for (auto item : jsonArray)
    {
        QJsonObject obj = item.toObject();
        //QString::number(alterjson["age"].toInt())
        QString itemId = QString("%1").arg(obj["id"].toInt());
        QString itemName = obj["name"].toString();
        QString itemPhone = obj["phone"].toString();
        QString itemStartDate = obj["start_date"].toString();
        QString itemExpireDate = obj["expirat_date"].toString(); // 注意：这里应该是"expire_date"而不是"expirat_date"

        QString listItem = QString("序号: %1\t 投递单位: %2\t 联系电话: %3\t 投放日期: %4\t 失效日期: %5")
            .arg(itemId, itemName, itemPhone, itemStartDate, itemExpireDate);
        ui->listWidget->addItem(listItem);
    }
}
