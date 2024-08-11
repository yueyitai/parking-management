#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addBt_clicked();

    void on_deleteBt_clicked();

    void on_alterBt_clicked();

    void on_lookBt_clicked();

    //接受查看返回的数据
    void recvData(QString data);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
