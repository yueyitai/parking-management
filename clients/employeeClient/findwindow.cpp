#include "findwindow.h"
#include "ui_findwindow.h"
#include "EClient.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
findwindow::findwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::findwindow),
    currentPage(0),
    itemsPerPage(10),
    i(1)
{
    ui->setupUi(this);
    ui->widgetAll->setText("智慧园区员工管理系统");
    //loadJsonData();
    setupPagination();
}

findwindow::~findwindow()
{
    delete ui;
}
//返回主菜单
void findwindow::on_backButton2_clicked()
{
    if (this->parentWidget()) {
            this->parentWidget()->show();
        }
    delete  this; // 或者使用 hide();
}

//向服务器发送请求信息  接受字符串解析制作成表格在tablewight中显示
void findwindow::on_findOneButton_clicked()
{
    // 清空表格
    ui->tableWidget->clear();

    // 创建 EClient 对象
    EClient client;

    // 创建 JSON 对象并设置查询条件
    QJsonObject findjson;
    findjson["id"] = ui->findIdEdit->text().toInt();
    QJsonDocument json(findjson);
    QByteArray jsonData = json.toJson(QJsonDocument::Compact);
    QString findString = QString::fromUtf8(jsonData);
    qDebug().noquote() << "JSON String:" << findString;

    // 定义接收缓冲区
    QString recvbuf;

    // 发送查询请求
    client.operateDatabase(EClient::ECLIENT_QUERY_ONE_INFO_BY_ID, &recvbuf, findString);

    // 打印返回的 JSON 数据
    qDebug().noquote() << "Received JSON:" << recvbuf;

    // 解析返回的 JSON 数据
    QJsonDocument doc = QJsonDocument::fromJson(recvbuf.toUtf8());
    QJsonObject jsonObject = doc.object(); // 假设返回的是一个 JSON 对象

    // 配置表格
    ui->tableWidget->setRowCount(1); // 只有一行数据
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels({"id", "姓名", "性别", "年龄", "入职时间", "是否在职", "离职时间", "手机号", "车牌号"});

    // 填充表格数据
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(jsonObject["id"].toInt())));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(jsonObject["name"].toString()));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(jsonObject["gender"].toString()));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(QString::number(jsonObject["age"].toInt())));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(jsonObject["hir_time"].toString()));
    ui->tableWidget->setItem(0, 5, new QTableWidgetItem(jsonObject["state"].toBool() ? "在职" : "离职"));
    ui->tableWidget->setItem(0, 6, new QTableWidgetItem(jsonObject["res_time"].toString()));
    ui->tableWidget->setItem(0, 7, new QTableWidgetItem(jsonObject["phone"].toString()));
    ui->tableWidget->setItem(0, 8, new QTableWidgetItem(jsonObject["licence_plate"].toString()));
}

//上一页逻辑
void findwindow::on_prevButton_clicked()
{
    if(i>1)
    {
        i--;
    }
    QString str = QString("第 %1 页").arg(i);
    ui->textlabel->setText(str);

    ui->tableWidget->clear();
    if (currentPage > 0) {
        --currentPage;
        on_pushButton_clicked();
    }
}
//下一页逻辑
void findwindow::on_nextButton_clicked()
{
    i++;
    QString str = QString("第 %1 页").arg(i);
    ui->textlabel->setText(str);

    ui->tableWidget->clear();
    if ((currentPage + 1) * itemsPerPage < jsonArray.size()) {
        ++currentPage;
        on_pushButton_clicked();
    }
}
//查询数据库全部信息显示到tablewight上每页十行，超过的翻页
void findwindow::on_pushButton_clicked()
{
    QString allBuf;
    EClient client1;
    client1.operateDatabase(EClient::ECLIENT_GET_ALL_INFO,&allBuf,nullptr);
    qDebug().noquote()<<"data:"<<allBuf;
    QJsonDocument doc = QJsonDocument::fromJson(allBuf.toUtf8());
    jsonArray = doc.array();

    QString str = QString("第 %1 页").arg(i);
    ui->textlabel->setText(str);

    ui->tableWidget->setRowCount(itemsPerPage);
    ui->tableWidget->setColumnCount(9);
    //你自己的键名
    ui->tableWidget->setHorizontalHeaderLabels({"id", "姓名","性别","年龄","入职时间","是否在职"
                                               ,"离职时间","手机号","车牌号"});

    int start = currentPage * itemsPerPage;
    int end = qMin(start + itemsPerPage, jsonArray.size());
    //根据键获得值生成新的表格显示在tablewight上
    for (int i = start; i < end; ++i) {
        QJsonObject obj = jsonArray[i].toObject();
        ui->tableWidget->setItem(i - start, 0, new QTableWidgetItem(QString::number(obj["id"].toInt())));
        ui->tableWidget->setItem(i - start, 1, new QTableWidgetItem(obj["name"].toString()));
        ui->tableWidget->setItem(i - start, 2, new QTableWidgetItem(obj["gender"].toString()));
        ui->tableWidget->setItem(i - start, 3, new QTableWidgetItem(QString::number(obj["age"].toInt())));
        ui->tableWidget->setItem(i - start, 4, new QTableWidgetItem(obj["hir_time"].toString()));
        ui->tableWidget->setItem(i - start, 5, new QTableWidgetItem(obj["state"].toBool() ? "在职" : "离职"));
        ui->tableWidget->setItem(i - start, 6, new QTableWidgetItem(obj["res_time"].toString()));
        ui->tableWidget->setItem(i - start, 7, new QTableWidgetItem(obj["phone"].toString()));
        ui->tableWidget->setItem(i - start, 8, new QTableWidgetItem(obj["licence_plate"].toString()));
    }

    ui->prevButton->setEnabled(currentPage > 0);
    ui->nextButton->setEnabled(end < jsonArray.size());
}

//设置分页的逻辑
void findwindow::setupPagination()
{
    //没有更多上一页就会false
    ui->prevButton->setEnabled(false);
    //下一页逻辑没有这么多数据就会false
    if (jsonArray.size() <= itemsPerPage) {
        ui->nextButton->setEnabled(false);
    }
}
