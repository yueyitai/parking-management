#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTime>
#include <QDate>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFileInfo>
#include <QBuffer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fee_Lb->setWordWrap(true);
    this->statusBar()->hide();
    //把定时器timeout与槽函数关联
    connect(&mtimer,&QTimer::timeout,this,&MainWindow::time_function);

    connect(this, SIGNAL(PictureClickFinished()), this, SLOT(in_out_park()));
    //启动
    mtimer.start(1000);

    server = new QTcpServer(this);
    if(!server->listen(QHostAddress::Any,20000))
    {
        qDebug()<<"server open fail"<<server->errorString();

    }
    connect(server,&QTcpServer::newConnection,this,&MainWindow::onNewConnection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection()
{
    clientSocket = server->nextPendingConnection();

}

void MainWindow::time_function()
{

    //获取系统时间
    QString datestr = QDate::currentDate().toString("yyyy-MM-dd");
    QString timestr = QTime::currentTime().toString("hh:mm:ss");
    ui->date_Lb->setText(datestr);
    ui->time_Lb->setText(timestr);
    QDateTime now = QDateTime::currentDateTime();
    uptimestamp = now.toMSecsSinceEpoch() / 1000;
}

int MainWindow::on_vedio_Bt_clicked()
{
    //1.打开设备
   fd = open("/dev/video7",O_RDWR);
   if(fd <0)
   {
       perror("open error");
       return -1;
   }
   //配置摄像头采集格式VIDIOC_S_FMT
   struct v4l2_format vformat;
   vformat.type= V4L2_BUF_TYPE_VIDEO_CAPTURE;
   vformat.fmt.pix.width = 640;
   vformat.fmt.pix.height = 480;
   vformat.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;

   int ret = ioctl(fd,VIDIOC_S_FMT,&vformat);
   if(ret<0)
   {
       perror("设置格式错误");
       return -1;
   }
   //申请缓冲区，VIDIOC_REQBUFS,
   //映射VIDIOC_QUERYBUF获取缓存区权限
   //VIDIOC_QBUF释放缓冲区权限
   struct v4l2_requestbuffers vreq;
   vreq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   vreq.count = 4;//申请缓冲区个数
   vreq.memory = V4L2_MEMORY_MMAP;//设置内存为映射
   ret = ioctl(fd,VIDIOC_REQBUFS,&vreq);
   if(ret<0)
   {
       perror("设置格式错误");
       return -1;
   }
   //获取缓冲区权限

   unsigned int mptrsize[4]= {0};
   struct v4l2_buffer vbuf;
   vbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   for(int i=0;i<4;i++)
   {
       vbuf.index = i;
       //获取缓冲区VIDIOC_QUERYBUF
       ret = ioctl(fd,VIDIOC_QUERYBUF,&vbuf);
       if(ret<0)
       {
           perror("querybuf error");
           return -1;
       }
       //映射
       void*ptr = mmap(NULL,vbuf.length,PROT_READ|PROT_WRITE,MAP_SHARED,fd,vbuf.m.offset);
       mptr[i] = static_cast<unsigned char*>(ptr);
       if(ptr == MAP_FAILED)
       {
           perror("map");
           return -1;
       }
       mptrsize[i]= vbuf.length;
       //把缓冲区放入捕获队列VIDIOC_QBUF
       ret = ioctl(fd,VIDIOC_QBUF,&vbuf);
       if(ret<0)
       {
           perror("qbuf");
           return -1;
       }
   }

   //采集数据
   //VIDIOC_DQBUF(把获取数据的缓冲区出队操作) VIDIOC_QBUF(释放)
   //开启流VIDIOC_STREAMON
   int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   ret = ioctl(fd,VIDIOC_STREAMON,&type);

   timerid = startTimer(100);

}

void MainWindow::timerEvent(QTimerEvent *e)
{
    struct v4l2_buffer vbuffer;
    vbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vbuffer.index = i;//获取第i个缓冲区
    int ret = ioctl(fd,VIDIOC_DQBUF,&vbuffer);//从内核中获取一个缓冲区

    //获取YUYV422->RGB888
    MainWindow::yuyv_to_rgb888(mptr[i],rgbdata,640,480);
    for(int r=0; r<480; r++)
    {
       for(int c=0; c<640; c++)
       {
           memcpy(q+c*3+r*640*3, rgbdata+((480-1-r)*640*3+c*3), 3);
       }

    }
    //printf("照片大小%d",sizeof(rgbdata));
    // 创建QImage对象，从指针q中加载图像数据
     QImage image(q, 640, 480, QImage::Format_RGB888);
     // 将QImage设置到QLabel上
     ui->vedio_Lb->setPixmap(QPixmap::fromImage(image));

    //VIDIOC_QBUF(将缓冲区放入捕获队列中)
    ret= ioctl(fd,VIDIOC_QBUF,&vbuffer);
    i++;
    i = i%4;
}


bool MainWindow::yuyv_to_rgb888(unsigned char*yuyvdata,unsigned char*rgbdata,int picw,int pich)
{
    int i,j;
    unsigned char y1,y2,u,v;
    int r1,g1,b1,r2,g2,b2;
    if(yuyvdata == NULL||rgbdata == NULL)
    {
        return false;
    }
    int tmpw = picw/2;
    for(i=0; i<pich; i++)
    {
        for(j=0; j<tmpw; j++)
        {
            y1 = *(yuyvdata + (i*tmpw+j)*4);
            u  = *(yuyvdata + (i*tmpw+j)*4+1);
            y2 = *(yuyvdata + (i*tmpw+j)*4+2);
            v  = *(yuyvdata + (i*tmpw+j)*4+3);

            r1 = y1 + 1.042*(v-128);
            g1 = y1 - 0.34414*(u-128);
            b1 = y1 + 1.772*(u-128);
            r2 = y2 + 1.042*(v-128);
            g2 = y2 - 0.34414*(u-128);
            b2 = y2 + 1.772*(u-128);
            if(r1 > 255) r1=255;
            else if(r1 < 0) r1 = 0;
            if(g1 > 255) g1=255;
            else if(g1 < 0) g1 = 0;
            if(b1 > 255) b1=255;
            else if(b1 < 0) b1 = 0;
            if(r2 > 255) r2=255;
            else if(r2 < 0) r2 = 0;
            if(g2 > 255) g2=255;
            else if(g2 < 0) g2 = 0;
            if(b2 > 255) b2=255;
            else if(b2 < 0) b2 = 0;
            rgbdata[((pich-1-i)*tmpw+j)*6]     = (unsigned char)b1;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 1] = (unsigned char)g1;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 2] = (unsigned char)r1;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 3] = (unsigned char)b2;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 4] = (unsigned char)g2;
            rgbdata[((pich-1-i)*tmpw+j)*6 + 5] = (unsigned char)r2;
        }
    }
    return true;
}

void MainWindow::on_picture_Bt_clicked()
{
    //缩放图像
    unsigned char q1[160*120*3] = {};
    for(int r=0; r<120; r++)
    {
       for(int c=0; c<160; c++)
       {
           memcpy(q1+r*160*3+c*3, q+r*4*640*3+c*3*4, 3);
       }
    }

    // 创建QImage对象，从指针q1中加载图像数据
     QImage image(q1, 160, 120, QImage::Format_RGB888);
     ui->picture_Lb->setPixmap(QPixmap::fromImage(image));
     QPixmap pixmap = ui->picture_Lb->pixmap()->copy();
     pixmap.save("./saved_image.jpg");

    //从指针q中加载图像数据,读取并上传服务器
    QImage image1(q, 640, 480, QImage::Format_RGB888);
    image1.save("./upload_image.jpg");
    QPixmap pixmap1 = QPixmap::fromImage(image1);
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    pixmap1.save(&buffer, "JPG");
    buffer.close();
    QFileInfo fileInfo("./upload_image.jpg");
    QString fileName = fileInfo.fileName();

    //上传qjson格式的数据
    QJsonObject contentObj;
    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 获取当前日期
    QDate currentDate = currentDateTime.date();

    // 获取当前时间
    QTime currentTime = currentDateTime.time();
    QString currentDateStr = currentDate.toString("yyyy-MM-dd");
    QString currentTimeStr = currentTime.toString("HH-mm-ss");
    QString str1 = QString("%1_%2.jpg").arg(currentDateStr).arg(currentTimeStr);
    contentObj["name"]= str1;
    contentObj["size"]= imageData.size();
    QJsonObject rootObj;
    rootObj["image"] = contentObj;
    rootObj["time"] = uptimestamp;
    QJsonDocument jsonDoc(rootObj);
    QByteArray jsonByteArray = jsonDoc.toJson(QJsonDocument::Compact);
    QString jsonString = QString::fromUtf8(jsonByteArray);

    //链接服务器
    EClient client;
    plate.clear();
    if(!client.operateDatabase(EClient::PCLIENT_INSERT_ONE_INFO, nullptr, jsonString))
    {
        qDebug()<<"operateDatabase fail";
    }
    else
    {
        qDebug()<<"operateDatabase success";
    }

    //给服务器发送照片数据
    int ret = client.socket->write(imageData.constData(),imageData.size());
    qDebug()<<"ret:"<<ret<<"imageData.size():"<<imageData.size();
    if(ret < 0)
    {
        qDebug()<<"write fail";
    }
    if(!client.socket->waitForBytesWritten(10000))
    {
        qDebug()<<"waitForBytesWritten";
    }

    //获取车牌号
    // 等待数据准备好
    if (!client.socket->waitForReadyRead(10000)) {
        qDebug() << "Error waiting for response:" << client.socket->errorString();
    }
    // 读取响应数据的长度
    qint64 plateSize;
    qint64 bytesRead = client.socket->read(reinterpret_cast<char*>(&plateSize), sizeof(plateSize));
    if (bytesRead != sizeof(plateSize)) {
        qDebug() << "Error reading plate size:" << client.socket->errorString();
    }
    qDebug() << "Expected plate size:" << plateSize;
    if (!client.socket->waitForReadyRead(10000)) {
        qDebug() << "Error waiting for response:" << client.socket->errorString();
    }
    // 确保读取内容时，响应数据大小正确
    QByteArray responseBuf(plateSize, 0);
    qint64 bytesReadContent = client.socket->read(responseBuf.data(), plateSize);
    if (bytesReadContent != plateSize) {
        qDebug() << "Error reading response data: Expected" << plateSize << "bytes, but got" << bytesReadContent << "bytes.";
        qDebug() << "Error message:" << client.socket->errorString();
    }
    str_plate = QString::fromUtf8(responseBuf);
    if(str_plate != "null")
    {
        qDebug()<<str_plate;
        ui->car_num_Lb->setText(str_plate);

        emit PictureClickFinished();
    }
    else
    {

    }
}


void MainWindow::on_change_Bt_clicked()
{
    InputWindow*Win = new InputWindow(this);
    Win->show();
    connect(Win,&InputWindow::sendData,this,&MainWindow::recvData);
    this->hide();
}
void MainWindow::recvData(QString data)
{
    ui->fee_Ed->setText(data);
    bool ok;
    show_fee = data.toDouble(&ok);
}

void MainWindow::in_out_park()
{
    qDebug()<<"1111111111111111111";
    //获取进出场查询信息(time,flag)
    EClient client;
    qint32 load_timestamp;//接受的时间戳
    QString load_info;
    QJsonObject plate_json;
    plate_json["licence_plate"]=str_plate;
    QJsonDocument jsonDoc(plate_json);
    QByteArray jsonB = jsonDoc.toJson();
    plate = QString(jsonB);
    if(client.operateDatabase(EClient::PCLIENT_QUERY_ONE_INFO_BY_PLATE,&load_info, plate))
    {
        qDebug()<<"query success";
        qDebug()<<load_info;
        QJsonDocument jsonDoc1 = QJsonDocument::fromJson(load_info.toUtf8());
        if (jsonDoc1.isNull())
        {
            qDebug() << "Failed to parse the JSON string";
        } else
        {
            QJsonObject jsonObj = jsonDoc1.object();
            load_timestamp = jsonObj["time"].toInt();
            int flag = jsonObj["flag"].toInt();
            if(load_timestamp>0)
            {
                if(flag == 0)
                {
                    double all_fee = (uptimestamp-load_timestamp)*show_fee;
                    QString str = QString("welcome %1 car owner come again，please pay:%2").arg(str_plate).arg(all_fee);
                    qDebug()<<str;
                    //ui->show_Lb->setText(str);
                    QJsonObject jsonObj;
                    jsonObj["show_Lb"] = str;
                    QJsonDocument jsonDoc;
                    jsonDoc.setObject(jsonObj);
                    QByteArray jsonByteArray = jsonDoc.toJson(QJsonDocument::Compact);
                    QString jsonString = QString::fromUtf8(jsonByteArray);
                    if (clientSocket->state() == QAbstractSocket::ConnectedState)
                    {
                        qDebug()<<"client have connect";
                        clientSocket->write(jsonString.toUtf8());
                    }
                    else
                    {
                        qDebug() << "client not connect";
                    }
                }
                if(flag>0)
                {
                    QString str = QString("welcome %1 car owner come again").arg(str_plate);
                    qDebug()<<str;
                    //ui->show_Lb->setText(str);
                    QJsonObject jsonObj;
                    jsonObj["show_Lb"] = str;
                    QJsonDocument jsonDoc;
                    jsonDoc.setObject(jsonObj);
                    QByteArray jsonByteArray = jsonDoc.toJson(QJsonDocument::Compact);
                    QString jsonString = QString::fromUtf8(jsonByteArray);
                    if (clientSocket->state() == QAbstractSocket::ConnectedState)
                    {
                        qDebug()<<"client have connect";
                        clientSocket->write(jsonString.toUtf8());
                    }
                    else
                    {
                        qDebug() << "client not connect";
                    }
                }
            }
            if(load_timestamp == 0)
            {
                if(flag == 0)
                {
                    QString str = QString("welcome owner %1 go home").arg(str_plate);
                    qDebug()<<str;
                    //ui->show_Lb->setText(str);
                    QJsonObject jsonObj;
                    qDebug()<<"1111111111122222";
                    jsonObj["show_Lb"] = str;
                    qDebug()<<"1111111111133333";
                    QJsonDocument jsonDoc;
                    qDebug()<<"1111111111144444";
                    jsonDoc.setObject(jsonObj);
                    qDebug()<<"1111111111155555";
                    QByteArray jsonByteArray = jsonDoc.toJson(QJsonDocument::Compact);
                    qDebug()<<"1111111111166666";
                    QString jsonString = QString::fromUtf8(jsonByteArray);
                    qDebug()<<"1111111111177777";
                    if (clientSocket->state() == QAbstractSocket::ConnectedState)
                    {
                        qDebug()<<"client have connect";
                        clientSocket->write(jsonString.toUtf8());
                    }
                    else
                    {
                        qDebug() << "client not connect";
                    }
                }

            }
        }
    }
    else
    {
        qDebug()<<"query fail";
    }
}

