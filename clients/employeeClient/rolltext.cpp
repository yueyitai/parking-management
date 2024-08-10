#include "rolltext.h"

#include <QPainter>

RollText::RollText(QWidget *parent) : QWidget(parent)
{

    x = 0;
    startTimer(20);
    QFont font = this->font();
    font.setPixelSize(this->height());
    this->setFont(font);
}

void RollText::setText(QString text)
{
    this->text = text;
}

void RollText::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    int fh = painter.fontMetrics().height(); //获取字体高
    painter.drawText(x,this->height()/2.0+fh/2.0,this->text);
    if(x<0){
        painter.drawText(this->width()+x,this->height()/2.0+fh/2.0,this->text);
    }
    int w = QFontMetrics(this->font()).width(this->text);//根据字体大小获取字符串所占用的长度
    if(x<-w)x = this->width()-w;
}

void RollText::timerEvent(QTimerEvent *e)
{
    x--;
    update();
}
