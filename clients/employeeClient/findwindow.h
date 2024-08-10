#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QMainWindow>
#include <QJsonArray>

namespace Ui {
class findwindow;
}

class findwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit findwindow(QWidget *parent = nullptr);
    ~findwindow();

private slots:
    void on_backButton2_clicked();
    void on_findOneButton_clicked();
    void on_prevButton_clicked();
    void on_nextButton_clicked();
    void on_pushButton_clicked();

private:
    Ui::findwindow *ui;
    int currentPage;
    int itemsPerPage;
    QJsonArray jsonArray;
    int i;
    void setupPagination();


};

#endif // FINDWINDOW_H
