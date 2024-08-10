#pragma once

#include <QTcpSocket>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

class EClient : public QObject
{

public:
    enum OptCode
    {
        PCLIENT_QUERY_ONE_INFO_BY_PLATE = 301,                      //根据车牌查询单条
        PCLIENT_INSERT_ONE_INFO,                                    //插入单条停车信息
        PCLIENT_DELETE_ONE_INFO_BY_PLATE,	                        //根据车牌删除单条
        PCLIENT_QUERY_PLATE_EXISTENCE_IN_EMPLOYEE_TABLE_BY_PLATE,	//根据车牌查询员工信息中是否存在该车牌
        PCLIENT_QUERY_PLATE_EXISTENCE_IN_VIP_TABLE_BY_PLATE,		//根据车牌查询vip信息中是否存在该车牌

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
