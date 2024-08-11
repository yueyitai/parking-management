#ifndef ALTER_H
#define ALTER_H

#include <QMainWindow>

namespace Ui {
class alter;
}

class alter : public QMainWindow
{
    Q_OBJECT

public:
    explicit alter(QWidget *parent = nullptr);
    ~alter();


private slots:
    void on_alterEnt_clicked();

    void on_alterBreak_clicked();


    //接受查看返回的数据
    void recvAlter1Data(QString data);

private:
    Ui::alter *ui;
};

#endif // ALTER_H
