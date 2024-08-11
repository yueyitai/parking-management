#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H
#include "addwindow.h"
#include "alterwindow.h"
#include "findwindow.h"
#include <QMainWindow>

namespace Ui {
class initialwindow;
}

class initialwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit initialwindow(QWidget *parent = nullptr);
    ~initialwindow();

private slots:
    void on_addButton_clicked();

    void on_findButton_clicked();

    void on_alterButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::initialwindow *ui;
};

#endif // INITIALWINDOW_H
