#ifndef ALTERWINDOW_H
#define ALTERWINDOW_H

#include <QMainWindow>

namespace Ui {
class alterwindow;
}

class alterwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit alterwindow(QWidget *parent = nullptr);
    ~alterwindow();

private slots:
    void on_backButton3_clicked();

    void on_alterFindButton_clicked();

    void on_alterAllButton_clicked();

private:
    Ui::alterwindow *ui;

};

#endif // ALTERWINDOW_H
