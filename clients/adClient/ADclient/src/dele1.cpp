#include "inc/dele1.h"
#include "ui_dele1.h"
#include "inc/EClient.h"

#include <QMessageBox>

dele1::dele1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dele1)
{
    ui->setupUi(this);
}

dele1::~dele1()
{
    delete ui;
}


void dele1::on_delEnt_clicked()
{
    QString buf = "1";
    QJsonObject image;  //{}
    image.insert("id",buf.toInt());
    //把json数据转换为字符串
    QJsonDocument doc;
    doc.setObject(image);
    QString sentBuff;
    sentBuff = doc.toJson();  //转字符串

    EClient client;
    bool tem = client.operateDatabase(EClient::ADCLIENT_DELETE_ONE_INFO_BY_ID,nullptr,sentBuff);
    if(tem)
    {
        QMessageBox::information(this, "提示", "删除成功");
        delete this;
    }
    else
    {
        QMessageBox::information(this, "提示", "删除失败");
    }


}

