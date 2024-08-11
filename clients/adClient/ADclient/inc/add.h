#ifndef ADD_H
#define ADD_H

#include <QMainWindow>

namespace Ui {
class add;
}

class add : public QMainWindow
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = nullptr);
    ~add();

private slots:
    void on_enter_clicked();

    void on_lookBt_clicked();

    void on_pushButton_clicked();

private:
    Ui::add *ui;
};

#endif // ADD_H
