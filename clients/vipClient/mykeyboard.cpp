#include "mykeyboard.h"
#include "ui_mykeyboard.h"

#include <QLineEdit>

MyKeyBoard::MyKeyBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyKeyBoard)
{
    ui->setupUi(this);
}

MyKeyBoard::~MyKeyBoard()
{
    delete ui;
}

void MyKeyBoard::on_clear_button_clicked()
{
    // 获取当前焦点的窗口部件
    QWidget *focusedWidget = QApplication::focusWidget();

    // 检查当前焦点的窗口部件是否为 QLineEdit
    QLineEdit *focusedLineEdit = qobject_cast<QLineEdit*>(focusedWidget);

    if (focusedLineEdit)
    {
        // 获取当前文本
        QString text = focusedLineEdit->text();

        // 检查文本是否为空
        if (!text.isEmpty())
        {
            // 移除最后一位字符
            text.chop(1);

            // 更新 QLineEdit 的文本
            focusedLineEdit->setText(text);
        }
    }
}
