#include "widget.h"
#include "ui_widget.h"

#include <QDate>
#include <QDebug>
#include <QFileDialog>
#include <QImageWriter>
#include <QMovie>
#include <QTimer>
#include <QUdpSocket>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//时间显示
    connect(&mtimer, &QTimer::timeout, this, &Widget::showTime);
    mtimer.start(1000);

//播放gif
    QMovie *movie = new QMovie(":/other/2.gif");
    ui->other->setMovie(movie);

    // 开始播放动画
    movie->start();

    // 创建定时器用于控制动画播放
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, movie, &QMovie::jumpToNextFrame);
    //timer->start(2000);
    // 设置窗口和标签的尺寸
    ui->other->setScaledContents(true); // 保持图片比例
    ui->other->setFixedSize(140, 140); // 设置标签的尺寸
    ui->num->setFixedSize(140, 140); // 设置标签的尺寸

//图片显示
    loadDirectory();
    QTimer::singleShot(5000, this, &Widget::showNextImage);


}

Widget::~Widget()
{
    delete ui;
}


//图片显示
void Widget::showNextImage()
{
    if (currentImageIndex >= images.count()) {
                currentImageIndex = 0; // 重置索引，实现循环
            }
    QImage image = images.at(currentImageIndex);
    QPixmap pixmap = QPixmap::fromImage(image).scaled(618, 407, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label->setPixmap(pixmap);
    currentImageIndex++;
    QTimer::singleShot(5000, this, &Widget::showNextImage); // 5秒后显示下一张图片
}

//图片预存
void Widget::loadDirectory()
{
    QString directory = QFileDialog::getExistingDirectory(this, "选择图片目录");
    QDir dir(directory);
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.gif"<< "*.bmp"; // 支持的图片格式
    QStringList files = dir.entryList(filters, QDir::Files);
    foreach (const QString &file, files) {
        images.append(QImage(dir.absoluteFilePath(file)));
    }
}



void Widget::showTime()
{
    ui->data->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    ui->time->setText(QTime::currentTime().toString("hh:mm:ss"));
}

