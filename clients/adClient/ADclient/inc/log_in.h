#ifndef LOG_IN_H
#define LOG_IN_H

#include <QMainWindow>

namespace Ui {
class log_in;
}

class log_in : public QMainWindow
{
    Q_OBJECT

public:
    explicit log_in(QWidget *parent = nullptr);
    ~log_in();

private slots:
    void on_login_clicked();

private:
    Ui::log_in *ui;
};

#endif // LOG_IN_H
