#ifndef LOOK_H
#define LOOK_H

#include <QMainWindow>

namespace Ui {
class look;
}

class look : public QMainWindow
{
    Q_OBJECT

public:
    explicit look(QWidget *parent = nullptr);
    ~look();

private slots:
    void on_pushButton_clicked();

signals:
    //自定义一个发送数据的信号
    void sendData(QString data);  //类似与函数声明但是不需要实现

private:
    Ui::look *ui;
};

#endif // LOOK_H
