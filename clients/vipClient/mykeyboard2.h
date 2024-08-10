#ifndef MYKEYBOARD2_H
#define MYKEYBOARD2_H

#include <QWidget>

namespace Ui {
class MyKeyBoard2;
}

class MyKeyBoard2 : public QWidget
{
    Q_OBJECT

public:
    explicit MyKeyBoard2(QWidget *parent = nullptr);
    ~MyKeyBoard2();

private slots:
    void on_clear_button_clicked();

private:
    Ui::MyKeyBoard2 *ui;
};

#endif // MYKEYBOARD2_H
