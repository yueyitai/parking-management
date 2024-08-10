#ifndef USER2VIP_H
#define USER2VIP_H

#include <QWidget>

namespace Ui {
class User2vip;
}

class User2vip : public QWidget
{
    Q_OBJECT

public:
    explicit User2vip(QWidget *parent = nullptr);
    ~User2vip();

private slots:
    void on_keyboard_button_clicked();

    void on_register_button_clicked();

    void on_login_button_clicked();

private:
    Ui::User2vip *ui;
};

#endif // USER2VIP_H
