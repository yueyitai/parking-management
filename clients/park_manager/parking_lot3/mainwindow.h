#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <linux/fb.h>
#include <string.h>
#include <QTimer>
#include <QFile>
#include <QNetworkAccessManager>
#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>
#include "EClient.h"
#include "inputwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool yuyv_to_rgb888(unsigned char*yuyvdata,unsigned char*rgbdata,int picw,int pich);
    void timerEvent(QTimerEvent *e);
public slots:
    void in_out_park();
signals:
    void PictureClickFinished();
protected slots:
    void recvData(QString data);
private slots:
    void time_function();
    int on_vedio_Bt_clicked();
    void on_picture_Bt_clicked();
    void onNewConnection();

    void on_change_Bt_clicked();

private:
    Ui::MainWindow *ui;
    QTimer mtimer;
    int timerid;
    unsigned char rgbdata[640*480*3] = {};
    unsigned char q[640*480*3] = {};//显示的指针
    QTcpServer *server;
    QTcpSocket*clientSocket;

    int i=0;
    int fd;
    unsigned char*mptr[4]={0};
    QFile file;//上传照片
    QNetworkAccessManager manager;
    QByteArray allArray;
    qint32 uptimestamp;//发出时间戳
    double show_fee;//显示的钱数

    QString plate;//json格式的
    QString str_plate;//string车牌
};
#endif // MAINWINDOW_H
