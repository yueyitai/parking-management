#include "EClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#define SERVER_IP "192.168.1.32"
#define SERVER_PORT 20202

EClient::EClient(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    socket->connectToHost(SERVER_IP, SERVER_PORT);
    if (!socket->waitForConnected(3000)) {
        qDebug() << "Failed to connect to server:" << socket->errorString();
    }
}

EClient::~EClient()
{
    if (socket->isOpen()) {
        socket->disconnectFromHost();
    }
}

bool EClient::operateDatabase(OptCode optCode, QString * recvBuf , const QString &data)

{
    Request request;
    switch (optCode)
    {
    case ECLIENT_GET_ALL_INFO:
        request = { optCode, "EClientGetAllInfo", "null" };
        break;
    case ECLIENT_INSERT_ONE_INFO:
        request = { optCode, "EClientInsertOneInfo", data };
        break;
    case ECLIENT_QUERY_ONE_INFO_BY_ID:
        request = { optCode, "EClientQueryOneInfoById", "null" };
        break;
    case ECLIENT_UPDATE_ONE_INFO_BY_ID:
        request = { optCode, "EClientUpdateOneInfoById", data };
        break;
    default:
        return false;
    }

    QString requestStr;
    formatRequest(requestStr, request);

    if (!sendRequest(requestStr)) return false;

    QString responseStr;
    if (!recvResponse(responseStr)) return false;

    Response response;
    analyzeResponse(responseStr, response);

//    if (response.resultCode == RESPONSE_RESULT_SUCCESS) {
//        recvBuf = response.data;
//        return true;
//    }
    switch (response.resultCode)
    {
    case RESPONSE_RESULT_SUCCESS:
    {
        if(recvBuf != nullptr)
        {
            *recvBuf = response.data;
        }
        return true;
        break;
    }
    case RESPONSE_RESULT_FAIL:
    {

        return false;
        break;
    }
    }
}

void EClient::formatRequest(QString &requestStr, const Request &request)
{
    QJsonObject jsonHeader;
    jsonHeader["opt"] = request.opt;
    jsonHeader["opt_code"] = static_cast<int>(request.optCode);

    QJsonObject jsonBody;
    jsonBody["data"] = request.data;

    QJsonObject jsonRoot;
    jsonRoot["header"] = jsonHeader;
    jsonRoot["body"] = jsonBody;

    QJsonDocument doc(jsonRoot);
    requestStr = doc.toJson(QJsonDocument::Compact);
}

bool EClient::sendRequest(const QString &requestStr)
{
    QByteArray requestData = requestStr.toUtf8();
    qint64 requestSize = requestData.size();

    qint64 bytesWritten = socket->write(reinterpret_cast<const char*>(&requestSize), sizeof(requestSize));
    if (bytesWritten != sizeof(requestSize)) {
        qDebug() << "Error writing request size:" << socket->errorString();
        return false;
    }

    bytesWritten = socket->write(requestData);
    if (bytesWritten != requestSize) {
        qDebug() << "Error writing request data:" << socket->errorString();
        return false;
    }

    return socket->waitForBytesWritten();
}

bool EClient::recvResponse(QString &responseStr)
{
    // 等待数据准备好
    if (!socket->waitForReadyRead()) {
        qDebug() << "Error waiting for response:" << socket->errorString();
        return false;
    }
    // 读取响应数据的长度
    qint64 responseSize;
    qint64 bytesRead = socket->read(reinterpret_cast<char*>(&responseSize), sizeof(responseSize));
    if (bytesRead != sizeof(responseSize)) {
        qDebug() << "Error reading response size:" << socket->errorString();
        return false;
    }
    qDebug() << "Expected response size:" << responseSize;

    if (!socket->waitForReadyRead()) {
        qDebug() << "Error waiting for response:" << socket->errorString();
        return false;
    }

    // 确保读取内容时，响应数据大小正确
    QByteArray responseBuf(responseSize, 0);
    qint64 bytesReadContent = socket->read(responseBuf.data(), responseSize);
    if (bytesReadContent != responseSize) {
        qDebug() << "Error reading response data: Expected" << responseSize << "bytes, but got" << bytesReadContent << "bytes.";
        qDebug() << "Error message:" << socket->errorString();
        return false;
    }

    responseStr = QString::fromUtf8(responseBuf);
    qDebug().noquote()<<responseStr;
    return true;
}

void EClient::analyzeResponse(const QString &responseStr, Response &response)
{
    QJsonDocument doc = QJsonDocument::fromJson(responseStr.toUtf8());
    QJsonObject jsonRoot = doc.object();

    QJsonObject jsonHeader = jsonRoot["header"].toObject();
    QJsonObject jsonBody = jsonRoot["body"].toObject();

    response.result = jsonHeader["result"].toString();
    response.resultCode = static_cast<ResponseResultCode>(jsonHeader["result_code"].toInt());//返回成功或失败   成功100，失败200
    response.opt = jsonHeader["opt"].toString();
    response.optCode = static_cast<OptCode>(jsonHeader["opt_code"].toInt());
    response.data = jsonBody["data"].toString();
}
