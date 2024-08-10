#ifndef KEYGOOD_H
#define KEYGOOD_H

#include <QToolButton>

class Keygood : public QToolButton
{
public:
    Keygood(QWidget *parent = nullptr);
    ~Keygood();

protected:
    void button_clicked();
};

#endif // KEYGOOD_H
