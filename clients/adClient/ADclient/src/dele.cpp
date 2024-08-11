#include "inc/dele.h"
#include "ui_dele.h"
#include "inc/EClient.h"
#include "inc/dele1.h"

#include <QJsonArray>
#include <QMessageBox>


QString deleBuff;

bool tem;
dele::dele(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dele)
{
    ui->setupUi(this);

    EClient cli;
    tem = cli.operateDatabase(EClient::ADCLIENT_GET_ALL_INFO,&deleBuff,nullptr);
    if(tem)
    {
        QMessageBox::information(this, "提示", "查询成功");

        qDebug() << "删除查询的全部数据";
        qDebug() << deleBuff;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(deleBuff.toUtf8());
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


dele::~dele()
{
    delete ui;
}

void dele::on_delEnter_clicked()
{
    if(ui->delId->text() == "")
    {
        QMessageBox::information(this, "提示", "请正确输入需要操作的ID");
    }
    else
    {
        int ret = QMessageBox::question(this,"删除广告", "是否确认删除",QMessageBox::Yes, QMessageBox::No);
        if(ret == QMessageBox::Yes){
            QString buf = ui->delId->text();
            QJsonObject image;
            image.insert("id",buf.toInt());
            //把json数据转换为字符串
            QJsonDocument doc;
            doc.setObject(image);
            QString sentBuff;
            sentBuff = doc.toJson();  //转字符串
            EClient cli;
            tem = cli.operateDatabase(EClient::ADCLIENT_DELETE_ONE_INFO_BY_ID,nullptr,sentBuff);
            if(tem)
            {
                QMessageBox::information(this, "提示", "删除成功");
                //返回上一级窗口
                this->parentWidget()->show();
                delete this;//释放本窗口（第三个窗口）
            }
            else
            {
                QMessageBox::information(this, "提示", "删除失败");
            }
        }
    }
}

void dele::on_delBreak_clicked()
{
    //返回上一级窗口
    this->parentWidget()->show();
    delete this;//释放本窗口（第三个窗口）
}
