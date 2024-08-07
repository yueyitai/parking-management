#pragma once

#include "TcpClient.h"

class EClient
	:public TcpClient
{
public:
	enum optCode
	{
		//VIP管理系统对数据库的操作
		VIPCLIENT_INSERT_ONE_INFO = 401,	//插入单条vip信息
		VIPCLIENT_QUERY_ONE_INFO_BY_PLATE,	//根据车牌查询单条vip信息
		VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE	//根据车牌修改单条vip信息
	};

public:
	EClient();
	~EClient();
	bool operateDatabase(enum optCode optCode, char* recvBuf = nullptr, const char* data = nullptr);

private:
	enum responseResultCode
	{
		RESPONSE_RESULT_SUCCESS = 100,
		RESPONSE_RESULT_FAIL = 200,
	};

	/*-------request struct-------*/
	struct requestHeader
	{
		enum optCode optCode;
		std::string opt;
	};
	struct requestBody
	{
		std::string data;
	};
	struct request
	{
		struct requestHeader header;
		struct requestBody body;
	};
	/*-------response struct-------*/
	struct responseHeader
	{
		std::string result;
		enum responseResultCode resultCode;
		std::string opt;
		enum optCode optCode;
	};
	struct responseBody
	{
		std::string data;
	};
	struct response
	{
		struct responseHeader header;
		struct responseBody body;
	};

private:
	void _formatRequest(std::string& requestStr, struct request& request);
	bool _sendRequest(std::string& requestStr);
	void _analyzeResponse(std::string& responseStr, struct response& response);
	bool _recvResponse(std::string& responseStr);

};

