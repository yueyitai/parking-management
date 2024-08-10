#include "user2vip.h"
#include "ui_user2vip.h"
#include "mykeyboard.h"
#include "mykeyboard2.h"
#include "mainwindow.h"
#include "EClient.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

User2vip::User2vip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User2vip)
{
    ui->setupUi(this);
}

User2vip::~User2vip()
{
    delete ui;
}

void User2vip::on_keyboard_button_clicked()
{
    static int num = 0;
    static MyKeyBoard *my_keyBoard1 = NULL;
    static MyKeyBoard2 *my_keyBoard2 = NULL;
    if(num%2 == 0){
        //显示第一个界面
        if(my_keyBoard2!=NULL){
            //my_keyBoard2->hide();
            delete my_keyBoard2;
            my_keyBoard2 = NULL;
        }
        if(my_keyBoard1==NULL){
            my_keyBoard1 = new MyKeyBoard(this);
        }

        my_keyBoard1->setWindowFlags(Qt::Widget);
        my_keyBoard1->setGeometry(150,300,600,200);
        my_keyBoard1->show();
    }else{
        if(my_keyBoard1!=NULL){
            //my_keyBoard1->hide();
            delete my_keyBoard1;
            my_keyBoard1 = NULL;
        }
        //显示第二个界面
        if(my_keyBoard2==NULL){
            my_keyBoard2 = new MyKeyBoard2(this);
        }
        my_keyBoard2->setWindowFlags(Qt::Widget);
        my_keyBoard2->setGeometry(150,300,600,200);
        my_keyBoard2->show();
    }
    num+=1;
}



void User2vip::on_register_button_clicked()
{
    //手动输入车牌，获得车牌号
    QString licence_plate_number = ui->licence_plate_number_lineEdit->text();
    QString province_abbreviation = ui->province_comboBox->currentText();
    QString licence_plate = province_abbreviation + licence_plate_number;
    // 检查车牌号码是否为空
    if (licence_plate_number.isEmpty()) {
        QMessageBox::warning(this, "错误", "请输入车牌号码！");
        return;
    }
    // 验证车牌号码的长度（这里假设长度为6到8个字符，不包括省份缩写）
    if (licence_plate_number.length() < 6 || licence_plate_number.length() > 8) {
        QMessageBox::warning(this, "错误", "车牌号码长度不正确！");
        return;
    }
    // 验证车牌号码的字符（这里只检查是否包含非字母数字字符，根据实际需要调整）
    QRegExp regExp("[A-Za-z0-9]+");
    if (!regExp.exactMatch(licence_plate_number)) {
        QMessageBox::warning(this, "错误", "车牌号码包含非法字符！");
        return;
    }

    //获得车主姓名
    QString owner_name = ui->owner_name_lineEdit->text();

    //获得车主手机号
    QString owner_telephone = ui->owner_telephonr_lineEdit->text();
    if (owner_telephone.isEmpty()) {
        QMessageBox::warning(this, "错误", "电话号码不能为空！");
        return;
    }
    //检查电话号码是否只包含数字
    bool isNumberOnly = true;
    for (QChar ch : owner_telephone) {
        if (!ch.isDigit()) {
            isNumberOnly = false;
            break;
        }
    }
    if (!isNumberOnly) {
        QMessageBox::warning(this, "错误", "电话号码只能包含数字！");
        return;
    }
    if (owner_telephone.length() != 11) {
        QMessageBox::warning(this, "错误", "电话号码长度必须为11位！");
        return;
    }


    EClient ec;
    QString recv;
    //创建一个json
    QJsonObject j;
    j["owner_name"] = owner_name;
    j["owner_telephone"] = owner_telephone;
    j["licence_plate"] = licence_plate;
    QJsonDocument jsonDoc(j);
    //发送请求
    bool ret = ec.operateDatabase(EClient::VIPCLIENT_INSERT_ONE_INFO, &recv, jsonDoc.toJson());



    if(ret == true){
        MainWindow* w = new MainWindow(this);

        w->show();
        w->set_plate(licence_plate);
        ui->licence_plate_number_lineEdit->clear();
        ui->owner_name_lineEdit->clear();
        ui->owner_telephonr_lineEdit->clear();
        this->hide();

    }else{
        QMessageBox::warning(this, "错误", "注册失败！");
        //ui->owner_name_lineEdit->clear();
        ui->licence_plate_number_lineEdit->clear();
        ui->owner_name_lineEdit->clear();
        ui->owner_telephonr_lineEdit->clear();
    }
}

void User2vip::on_login_button_clicked()
{
    //手动输入车牌，获得车牌号
    QString licence_plate_number = ui->licence_plate_number_lineEdit->text();
    QString province_abbreviation = ui->province_comboBox->currentText();
    QString licence_plate = province_abbreviation + licence_plate_number;
    // 检查车牌号码是否为空
    if (licence_plate_number.isEmpty()) {
        QMessageBox::warning(this, "错误", "请输入车牌号码！");
        return;
    }
    // 验证车牌号码的长度（这里假设长度为6到8个字符，不包括省份缩写）
    if (licence_plate_number.length() < 6 || licence_plate_number.length() > 8) {
        QMessageBox::warning(this, "错误", "车牌号码长度不正确！");
        return;
    }
    // 验证车牌号码的字符（这里只检查是否包含非字母数字字符，根据实际需要调整）
    QRegExp regExp("[A-Za-z0-9]+");
    if (!regExp.exactMatch(licence_plate_number)) {
        QMessageBox::warning(this, "错误", "车牌号码包含非法字符！");
        return;
    }

    //获得车主姓名
    QString owner_name = ui->owner_name_lineEdit->text();

    //获得车主手机号
    QString owner_telephone = ui->owner_telephonr_lineEdit->text();
    if (owner_telephone.isEmpty()) {
        QMessageBox::warning(this, "错误", "电话号码不能为空！");
        return;
    }
    //检查电话号码是否只包含数字
    bool isNumberOnly = true;
    for (QChar ch : owner_telephone) {
        if (!ch.isDigit()) {
            isNumberOnly = false;
            break;
        }
    }
    if (!isNumberOnly) {
        QMessageBox::warning(this, "错误", "电话号码只能包含数字！");
        return;
    }
    if (owner_telephone.length() != 11) {
        QMessageBox::warning(this, "错误", "电话号码长度必须为11位！");
        return;
    }
    EClient ec;
    QString recv;
    //创建一个json
    QJsonObject j;
    j["owner_name"] = owner_name;
    j["owner_telephone"] = owner_telephone;
    j["licence_plate"] = licence_plate;
    QJsonDocument jsonDoc(j);
    //发送请求
    bool ret = ec.operateDatabase(EClient::VIPCLIENT_QUERY_ONE_INFO_BY_PLATE, &recv, jsonDoc.toJson());

    if(ret == true){
        MainWindow* w = new MainWindow(this);

        w->show();
        w->set_plate(licence_plate);
        ui->licence_plate_number_lineEdit->clear();
        ui->owner_name_lineEdit->clear();
        ui->owner_telephonr_lineEdit->clear();
        this->hide();
    }else{
        QMessageBox::warning(this, "错误", "登陆失败！");
        ui->owner_name_lineEdit->clear();
        ui->licence_plate_number_lineEdit->clear();
        ui->owner_name_lineEdit->clear();
        ui->owner_telephonr_lineEdit->clear();
    }
}
