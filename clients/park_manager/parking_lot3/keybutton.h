#ifndef KEYBUTTON_H
#define KEYBUTTON_H

#include <QObject>
#include <QToolButton>

class KeyButton : public QToolButton
{
public:
    explicit KeyButton(QWidget *parent = nullptr);
    ~KeyButton();
protected slots:
    void button_click();
};

#endif // KEYBUTTON_H
