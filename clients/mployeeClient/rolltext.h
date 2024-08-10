#ifndef ROLLTEXT_H
#define ROLLTEXT_H

#include <QWidget>

class RollText : public QWidget
{
    Q_OBJECT
public:
    explicit RollText(QWidget *parent = nullptr);
    void setText(QString text);
    void paintEvent(QPaintEvent* e);
    void timerEvent(QTimerEvent* e);
signals:

private:
    QString text;
    int x;
};

#endif // ROLLTEXT_H
