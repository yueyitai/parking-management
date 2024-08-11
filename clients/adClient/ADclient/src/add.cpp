#include "inc/add.h"
#include "ui_add.h"

#include "inc/EClient.h"

#include <QBuffer>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

add::add(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);
}

add::~add()
{
    delete ui;
}

void add::on_lookBt_clicked()
{
    //返回上一级窗口
    this->parentWidget()->show();
    delete this;//释放本窗口（第三个窗口）
}

//选择图片按钮
QString fileName;  //文件名
void add::on_pushButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::homePath(), "Images (*.png *.jpeg *.jpg *.bmp *.gif)");
    QFileInfo info(fileName);
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
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

//添加按钮
void add::on_enter_clicked()
{
    //信息都填充完毕
    if(ui->name->text() == "" || ui->start_time->text() == "" || ui->expirat_date->text() == "" || ui->content->text() == "" || ui->phone->text() == "")
    {
        QMessageBox::information(this, "提示", "请全部输入！");
    }
    else
    {
        int ret = QMessageBox::information(this, "提示", "是否添加",QMessageBox::Yes, QMessageBox::No);
        if(ret == QMessageBox::Yes)   //打包并发送
        {

            QFileInfo info(fileName);
            // 使用 QPixmap 将 QImage 转换为 QByteArray
            QByteArray imageData;
            QBuffer buffer(&imageData);
            buffer.open(QIODevice::WriteOnly);
            QPixmap pixmap(fileName);
            pixmap.save(&buffer, "JPG");
            buffer.close();

        //打包发送数据
            //定义image对象   图片的信息文件名 和  大小
            QJsonObject image;  //{}
            image.insert("name",info.fileName());
            image.insert("size",imageData.size());

            QJsonObject obj; //创建一个对象
            obj.insert("name",ui->name->text()); //往对象中插入一个键值对  文件名
            obj.insert("start_date",ui->start_time->text());//往对象中插入一个键值对   投放时间
            obj.insert("expirat_date",ui->expirat_date->text()); //往对象中插入一个键值对    失效时间
            obj.insert("image",image); //往对象中插入一个键值对    图片信息
            obj.insert("phone",ui->phone->text());//往对象中插入一个键值对    电话

            //把json数据转换为字符串
            QJsonDocument doc;
            doc.setObject(obj);
            QString sentBuff = doc.toJson();  //转字符串
            qDebug() << "添加的信息";
            qDebug() << sentBuff;

            //调用客户端发送信息
            EClient client;
            bool tem = client.operateDatabase(EClient::ADCLIENT_INSERT_ONE_INFO,nullptr,sentBuff);
            if(tem)
            {
                int ret = client.socket->write(imageData.constData(),imageData.size());
                if(ret < 0)
                {
                    qDebug()<<"write失败";
                    QMessageBox::information(this, "提示", "添加失败");
                }
                if(!client.socket->waitForBytesWritten(10000))
                {
                    qDebug()<<"waitForBytesWritten失败";
                    QMessageBox::information(this, "提示", "添加失败");
                }
                else
                {
                    QMessageBox::information(this, "提示", "添加成功");

                    ui->name->setText("");
                    ui->start_time->setText("");
                    ui->expirat_date->setText("");
                    ui->content->setText("");
                    ui->phone->setText("");
                    ui->label->clear();
                }
            }
            else
            {
                QMessageBox::information(this, "提示", "添加失败");
            }
        }
    }
}


//            // 创建QBuffer用于存储base64编码的数据
//            QBuffer buffer;
//            buffer.open(QIODevice::WriteOnly);

//            // 将QPixmap保存到QBuffer中，并使用base64编码
//            QByteArray byteArray;
//            QBuffer output(&byteArray);
//            if (pixmap.save(&output, "PNG") && output.seek(0))
//            {
//                // 将QByteArray转换为base64编码
//                base64String = byteArray.toBase64();
//            }
//            else
//            {
//                QMessageBox::warning(this, QStringLiteral("Error"), QStringLiteral("Failed to encode image to base64"));
//            }


//            // 将base64编码的字符串解码为QByteArray
//            QByteArray imageByteData = QByteArray::fromBase64(base64String.toUtf8());

//            // 使用QBuffer来从QByteArray中读取数据
//            QBuffer buff(&imageByteData);
//            buff.open(QIODevice::ReadOnly);

//            // 从buffer中读取数据并转换为QImage
//            QImage image;
//            if (image.load(&buff, "PNG")) { // 假设图片格式是PNG，根据实际情况调整
//                // 将QImage转换为QPixmap
//                QPixmap pixmap = QPixmap::fromImage(image);

//                // 将QPixmap设置到QLabel上
//                ui->label->setPixmap(pixmap);
//            } else {
//                QMessageBox::warning(this, QStringLiteral("Error"), QStringLiteral("Failed to decode image from base64"));
//            }
