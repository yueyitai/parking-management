#include "inc/look.h"
#include "ui_look.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include <inc/EClient.h>

QString lookBuff;

bool lookTem;
look::look(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::look)
{
    ui->setupUi(this);
    EClient lookCli;
    lookTem = lookCli.operateDatabase(EClient::ADCLIENT_GET_ALL_INFO,&lookBuff,nullptr);
    if(lookTem)
    {
        QMessageBox::information(this, "提示", "查询成功");

//        qDebug() << "删除查询的全部数据";
//        qDebug() << lookBuff;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(lookBuff.toUtf8());
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

look::~look()
{
    delete ui;
}

void look::on_pushButton_clicked()
{
    //返回上一级窗口
    this->parentWidget()->show();
    delete this;//释放本窗口（第三个窗口）
}
