#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <QPixmap>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_plate(QString data);
private slots:
    void on_checkBox_clicked(bool checked);

    void on_vip_month_pushbutton_clicked();

    void on_vip_quarter_pushbutton_clicked();

    void on_vip_year_pushbutton_clicked();

    void on_payment_button_clicked();

    void on_back_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
