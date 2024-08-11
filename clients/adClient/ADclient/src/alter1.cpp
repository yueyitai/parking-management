#include "inc/alter1.h"
#include "ui_alter1.h"
#include "inc/EClient.h"

#include <QBuffer>
#include <QFileDialog>
#include <QMessageBox>

alter1::alter1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::alter1)
{
    ui->setupUi(this);
}

alter1::~alter1()
{
    delete ui;
}

//接收alter窗口发来的信息
void alter1::receiveAlterData(QString data)
{
//    qDebug()<< "接受的信息";
//    qDebug()<< data;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = jsonDoc.object();

    QString itemId = QString("%1").arg(obj["id"].toInt());
    QString itemName = obj["name"].toString();
    QString itemPhone = obj["phone"].toString();
    QString itemStartDate = obj["start_date"].toString();
    QString itemExpireDate = obj["expirat_date"].toString(); // 注意：这里应该是"expire_date"而不是"expirat_date"


    ui->labelId->setText(itemId);
    ui->name->setText(itemName);
    ui->phone->setText(itemPhone);
    ui->start_time->setText(itemStartDate);
    ui->expirat_date->setText(itemExpireDate);
}


QString altFileName;

bool alter1Tem;
//图片选择
void alter1::on_pushButton_clicked()
{
    altFileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::homePath(), "Images (*.png *.jpeg *.jpg *.bmp *.gif)");
    QFileInfo info(altFileName);
    if (!altFileName.isEmpty())
    {
        QImage image(altFileName);
        qDebug()<<image;
        if (!image.isNull())
        {
            // 将QImage转换为QPixmap
            QPixmap pixmap = QPixmap::fromImage(image);
            //显示图片和文件名
            ui->label->setPixmap(pixmap);
            ui->content->setText(info.fileName());
        }
    }
}


//修改
void alter1::on_enter_clicked()
{
    if(ui->name->text() == "" || ui->start_time->text() == "" || ui->expirat_date->text() == "" || ui->phone->text() == "")
    {
        QMessageBox::information(this, "提示", "请全部输入！");
    }
    else
    {
        int ret = QMessageBox::information(this, "提示", "是否修改",QMessageBox::Yes, QMessageBox::No);
        if(ret == QMessageBox::Yes)   //打包并发送
        {
            QJsonObject obj; //创建一个对象

            obj.insert("id",ui->labelId->text());
            obj.insert("name",ui->name->text()); //往对象中插入一个键值对  文件名
            obj.insert("start_date",ui->start_time->text());//往对象中插入一个键值对   投放时间
            obj.insert("expirat_date",ui->expirat_date->text()); //往对象中插入一个键值对    失效时间
            obj.insert("image",ui->content->text()); //往对象中插入一个键值对    图片信息
            obj.insert("phone",ui->phone->text());//往对象中插入一个键值对    电话

            //把json数据转换为字符串
            QJsonDocument doc;
            doc.setObject(obj);
            QString sentBuff = doc.toJson();  //转字符串
//            qDebug() << "添加的信息";
//            qDebug() << sentBuff;

            EClient alter1Client;
            //调用客户端发送信息
            alter1Tem = alter1Client.operateDatabase(EClient::ADCLIENT_UPDATE_ONE_INFO_BY_ID,nullptr,sentBuff);
            if(alter1Tem)
            {
                alter1Tem = alter1Client.operateDatabase(EClient::ADCLIENT_GET_ALL_INFO,&sentBuff,nullptr);
                if(alter1Tem)
                {
                    //通过信号把data数据发送出去
                    emit sendAlterData(sentBuff);
                    QMessageBox::information(this, "提示", "修改成功");
                    delete this;
                }
                else
                {
//                    qDebug()<<"123失败";
                    QMessageBox::information(this, "提示", "修改失败");
                }
            }
            else
            {
//                qDebug()<<"123失败";
                QMessageBox::information(this, "提示", "修改失败");
            }
        }
    }
}
