#ifndef DELE1_H
#define DELE1_H

#include <QMainWindow>

namespace Ui {
class dele1;
}

class dele1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit dele1(QWidget *parent = nullptr);
    ~dele1();



private slots:
    void on_delEnt_clicked();

private:
    Ui::dele1 *ui;
};

#endif // DELE1_H
