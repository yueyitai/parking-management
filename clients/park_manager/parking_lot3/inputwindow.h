#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QMainWindow>

namespace Ui {
class InputWindow;
}

class InputWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InputWindow(QWidget *parent = nullptr);
    ~InputWindow();
private slots:

    void on_ok_Bt_clicked();
signals:
    void sendData(QString data);//信号不需要实现

private:
    Ui::InputWindow *ui;
};

#endif // INPUTWINDOW_H
