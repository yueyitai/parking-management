#pragma once
#include "ClientManager.h"
class ParkingServer :
    public ClientManager
{
public:
	ParkingServer(unsigned short serverPort);
	~ParkingServer();

private:
	enum optCode
	{
		ECLIENT_GETALLINFO = 101,
		ECLIENT_INSERT_ONE_INFO,
		ECLIENT_QUERY_ONE_INFO_BY_ID,
		ECLIENT_UPDATE_ONE_INFO_BY_ID
	};
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

    bool _handleData(int clientFD);
	void _handleRequest(std::string requestStr,int fd);
	void _createResponse(enum optCode optCode, std::string& opt, int fd);
	void _formatResponse(std::string& responseStr, struct response& response);
	void _sendResponse(std::string& responseStr, int fd);
};

