#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QMovie>
#include <QTimer>
#include <QUdpSocket>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void start();

private slots:
    void showNextImage();

    void showTime();

private:
    Ui::Widget *ui;

    QTimer timer;
    QTimer mtimer;
    int currentImageIndex = 0;
    QList<QImage> images;


    void loadDirectory();


};
#endif // WIDGET_H
