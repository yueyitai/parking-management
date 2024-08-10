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
		//员工管理系统对数据库的操作
		ECLIENT_GET_ALL_INFO = 101,		//获取全部员工信息
		ECLIENT_INSERT_ONE_INFO,		//插入单条员工信息
		ECLIENT_QUERY_ONE_INFO_BY_ID,	//根据id查询单条员工信息
		ECLIENT_UPDATE_ONE_INFO_BY_ID,	//根据id更新单条员工信息

		//广告系统对数据库的操作
		ADCLIENT_INSERT_ONE_INFO = 201,	//插入单条广告信息
		ADCLIENT_QUERY_ONE_INFO_BY_ID,	//根据id查询单条广告信息
		ADCLIENT_UPDATE_ONE_INFO_BY_ID,	//根据id修改单条广告信息
		ADCLIENT_DELETE_ONE_INFO_BY_ID,	//根据id删除单条广告信息
		ADCLIENT_GET_ALL_INFO,			//获取所有广告信息

		//停车场管理系统对数据库的操作
		PCLIENT_QUERY_ONE_INFO_BY_PLATE = 301,						//根据车牌查询单条信息
		PCLIENT_INSERT_ONE_INFO,									//插入单条停车信息
		PCLIENT_DELETE_ONE_INFO_BY_PLATE,							//根据车牌删除单条停车信息（修改is_delete）
		PCLIENT_QUERY_PLATE_EXISTENCE_IN_EMPLOYEE_TABLE_BY_PLATE,	//根据车牌查询员工信息中是否存在该车牌
		PCLIENT_QUERY_PLATE_EXISTENCE_IN_VIP_TABLE_BY_PLATE,		//根据车牌查询vip信息中是否存在该车牌

		//VIP管理系统对数据库的操作
		VIPCLIENT_INSERT_ONE_INFO = 401,	//插入单条vip信息
		VIPCLIENT_QUERY_ONE_INFO_BY_PLATE,	//根据车牌查询单条vip信息
		VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE	//根据车牌修改单条vip信息
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
	void _analyzeRequest(std::string& requestStr, struct request& request);
	void _handleImage(std::string data,int fd);
	void _changeJsonStr(std::string& baseRequestStr, std::string& newRequestStr, std::string* plateStr = nullptr);
	void _createResponse(enum optCode optCode, std::string& opt, int fd,std::string& inData);
	void _formatResponse(std::string& responseStr, struct response& response);
	void _sendResponse(std::string& responseStr, int fd);
	bool _recognizePlate(std::string& data, std::string& plateJsonStr);
	static size_t getHttpData(char* ptr, size_t size, size_t nmemb, void* userdata);
	void _analyzePlate(std::string& httpResponse, std::string& plateJsonStr);
	bool _sendPlate(int fd, std::string& plateJsonStr);
};

