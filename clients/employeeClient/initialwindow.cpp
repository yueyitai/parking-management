#include "initialwindow.h"
#include "ui_initialwindow.h"

#include <QMovie>
initialwindow::initialwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::initialwindow)
{
    ui->setupUi(this);
    ui->widget->setText("智慧园区员工管理系统");
    QMovie *movie = new QMovie(":/3.gif");

        // 设置 movie 到 QLabel 上
        ui->movietable->setMovie(movie);
        ui->movietable->setGeometry(0, 0, this->width()/2, this->height()/2);

        // 缩放 QLabel 尺寸以适应窗口大小

        ui->movietable->lower();
        // 开始播放 GIF 动图
        movie->start();

}


initialwindow::~initialwindow()
{
    delete ui;

}

void initialwindow::on_addButton_clicked()
{
    addwindow * add = new addwindow(this);
    add->show();
    this->hide();
}

void initialwindow::on_findButton_clicked()
{
    findwindow * find = new findwindow(this);
    find->show();
    this->hide();
}

void initialwindow::on_alterButton_clicked()
{
    alterwindow * alter = new alterwindow(this);
    alter->show();
    this->hide();
}

void initialwindow::on_quitButton_clicked()
{
    if (this->parentWidget()) {
            this->parentWidget()->show();
        }
    delete  this; // 或者使用 hide();
}
