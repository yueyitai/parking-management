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
        ECLIENT_GETALLINFO = 101,
        ECLIENT_INSERT_ONE_INFO,
        ECLIENT_QUERY_ONE_INFO_BY_ID,
        ECLIENT_UPDATE_ONE_INFO_BY_ID
    };

public:
    EClient(QObject *parent = nullptr);
    ~EClient();
    bool operateDatabase(OptCode optCode, QString &recvBuf, const QString &data = QString());

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

    QTcpSocket *socket;
};
