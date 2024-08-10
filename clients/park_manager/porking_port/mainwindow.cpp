#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    socket->connectToHost(SERVER_IP,SERVER_PORT);
    if(!socket->waitForConnected(3000))
    {
        qDebug()<<"porking_port fail";
    }
    connect(socket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);

}

MainWindow::~MainWindow()
{
    delete ui;
    if(socket->isOpen())
    {
        socket->disconnectFromHost();
    }
}

void MainWindow::onConnected()
{
    qDebug()<<"connect success";
}

void MainWindow::onReadyRead()
{
    QString load_info = socket->readAll();
    qDebug()<<load_info;
    //ui->show_Lb->setText(load_info);
    //获取显示信息的字符串
    QJsonDocument jsonDoc1 = QJsonDocument::fromJson(load_info.toUtf8());
    // 检查解析是否成功
    if (jsonDoc1.isNull())
    {
        qDebug() << "Failed to parse the JSON string";
    } else
    {
        // 解析成功，获取 QJsonObject
        QJsonObject jsonObj = jsonDoc1.object();
        QString key = jsonObj.keys().first();
        QJsonValue jsonValue = jsonObj.value(key);
        QString stringValue = jsonValue.toString();
        ui->show_Lb->setText(stringValue);
    }

}

