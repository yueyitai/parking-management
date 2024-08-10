#include "keybutton.h"

#include <QApplication>
#include <QMouseEvent>

KeyButton::KeyButton(QWidget *parent):QToolButton(parent)
{
   //关联本类的信号与槽函数
    connect(this, &KeyButton::clicked,this,&KeyButton::button_click);

}
KeyButton::~KeyButton()
{

}
void KeyButton::button_click()
{
    QString ch = this->text();
    char c = ch.at(0).toLatin1();//获取第一个字符
    //创建一个按下事件
    QKeyEvent*key = new QKeyEvent(QKeyEvent::KeyPress,c,Qt::NoModifier,ch);
    //派发事件
    QApplication::postEvent(QApplication::focusWidget(),key);

}
