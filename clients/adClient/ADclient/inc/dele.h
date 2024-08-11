#ifndef DELE_H
#define DELE_H

#include <QMainWindow>

namespace Ui {
class dele;
}

class dele : public QMainWindow
{
    Q_OBJECT

public:
    explicit dele(QWidget *parent = nullptr);
    ~dele();


private slots:
    void on_delEnter_clicked();

    void on_delBreak_clicked();

private:
    Ui::dele *ui;
};

#endif // DELE_H
