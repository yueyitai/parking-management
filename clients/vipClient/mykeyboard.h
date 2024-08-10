#ifndef MYKEYBOARD_H
#define MYKEYBOARD_H

#include <QWidget>

namespace Ui {
class MyKeyBoard;
}

class MyKeyBoard : public QWidget
{
    Q_OBJECT

public:
    explicit MyKeyBoard(QWidget *parent = nullptr);
    ~MyKeyBoard();

private slots:
    void on_clear_button_clicked();

private:
    Ui::MyKeyBoard *ui;
};

#endif // MYKEYBOARD_H
