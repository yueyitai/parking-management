#pragma once

#include <QTcpSocket>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

class EClient : public QObject
{
    Q_OBJECT

public:
    enum OptCode
    {
        //VIP管理系统对数据库的操作
        VIPCLIENT_INSERT_ONE_INFO = 401,	//注册
        VIPCLIENT_QUERY_ONE_INFO_BY_PLATE,	//登录
        VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE,	//付费


//        //广告系统对数据库的操作
//        ADCLIENT_INSERT_ONE_INFO = 201,	//插入单条广告信息
//        ADCLIENT_QUERY_ONE_INFO_BY_ID,	//根据id查询单条广告信息
//        ADCLIENT_UPDATE_ONE_INFO_BY_ID,	//根据id修改单条广告信息
//        ADCLIENT_DELETE_ONE_INFO_BY_ID,	//根据id删除单条广告信息
//        ADCLIENT_GET_ALL_INFO,			//获取所有广告信息

//        PCLIENT_INSERT_ONE_INFO = 302

    };

public:
    EClient(QObject *parent = nullptr);
    ~EClient();
    bool operateDatabase(OptCode optCode, QString *recvBuf = nullptr , const QString &data = QString());


private:
    enum ResponseResultCode
    {
        RESPONSE_RESULT_SUCCESS = 100,
        RESPONSE_RESULT_FAIL = 200,
    };

    struct Request
    {
        OptCode optCode;
        QString opt;
        QString data;
    };

    struct Response
    {
        QString result;
        ResponseResultCode resultCode;
        QString opt;
        OptCode optCode;
        QString data;
    };

private:
    void formatRequest(QString &requestStr, const Request &request);
    bool sendRequest(const QString &requestStr);
    void analyzeResponse(const QString &responseStr, Response &response);
    bool recvResponse(QString &responseStr);
public:
    QTcpSocket *socket;
};
