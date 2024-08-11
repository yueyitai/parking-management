#ifndef ALTER1_H
#define ALTER1_H

#include <QMainWindow>

namespace Ui {
class alter1;
}

class alter1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit alter1(QWidget *parent = nullptr);
    ~alter1();

    void receiveAlterData(QString data);


private slots:
    void on_pushButton_clicked();

    void on_enter_clicked();

signals:
    //自定义一个发送数据的信号
    void sendAlterData(QString data);  //类似与函数声明但是不需要实现


private:
    Ui::alter1 *ui;
};

#endif // ALTER1_H
