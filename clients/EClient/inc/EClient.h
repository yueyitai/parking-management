#pragma once

#include "TcpClient.h"

class EClient
	:public TcpClient
{
public:
	enum optCode
	{
		ECLIENT_GETALLINFO = 101,
		ECLIENT_INSERT_ONE_INFO,
		ECLIENT_QUERY_ONE_INFO_BY_ID,
		ECLIENT_UPDATE_ONE_INFO_BY_ID
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

