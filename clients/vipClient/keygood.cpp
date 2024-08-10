#include "keygood.h"

#include <QApplication>
#include <QKeyEvent>
#include <QDebug>

Keygood::Keygood(QWidget *parent):QToolButton(parent)
{
    connect(this, &Keygood::clicked, this, &Keygood::button_clicked);
}

Keygood::~Keygood()
{

}

void Keygood::button_clicked()
{
    QString ch = this->text();
    QKeyEvent *key = new QKeyEvent(QKeyEvent::KeyPress, ch.at(0).toLatin1(),Qt::NoModifier, ch);
    QApplication::postEvent(QApplication::focusWidget(), key);
}
