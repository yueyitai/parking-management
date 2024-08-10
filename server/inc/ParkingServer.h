#pragma once
#include "ClientManager.h"

class ParkingServer :
    public ClientManager
{
public:
	ParkingServer(unsigned short serverPort);
	~ParkingServer();

private:
	//操作识别码
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
		// PCLIENT_DELETE_ONE_INFO_BY_PLATE,							//根据车牌删除单条停车信息（修改is_delete）
		// PCLIENT_QUERY_PLATE_EXISTENCE_IN_EMPLOYEE_TABLE_BY_PLATE,	//根据车牌查询员工信息中是否存在该车牌
		// PCLIENT_QUERY_PLATE_EXISTENCE_IN_VIP_TABLE_BY_PLATE,		//根据车牌查询vip信息中是否存在该车牌

		//VIP管理系统对数据库的操作
		VIPCLIENT_INSERT_ONE_INFO = 401,	//插入单条vip信息
		VIPCLIENT_QUERY_ONE_INFO_BY_PLATE,	//根据车牌查询单条vip信息
		VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE	//根据车牌修改单条vip信息
	};

	//响应结果码
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

	/*
	作用 处理服务器接收的数据
	参数 clientFD 发来数据的套接字描述符
	*/
    bool _handleData(int clientFD);
	/*
	作用 处理接收到的请求，判断要做什么操作
	参数 requestStr 请求字符串
		 fd 目标套接字描述符
	*/
	void _handleRequest(std::string requestStr,int fd);
	/*
	作用 解析请求
	参数 requestStr 请求字符串
		 request 存放请求信息的结构体
	*/
	void _analyzeRequest(std::string& requestStr, struct request& request);
	/*
	作用 接收图片数据并存到本地
	参数 data 请求体中的数据字符串
		 fd 从该套接字描述符接收图片数据
	*/
	void _handleImage(std::string data,int fd);
	/*
	作用 修改请求信息为数据库所需格式
	参数 baseRequestStr 原请求字符串
		 newRequestStr 新请求字符串
		 plateStr 车牌号字符串，默认为空，有车牌号就会往新请求中json添加车牌号键值对
	*/
	void _changeJsonStr(std::string& baseRequestStr, std::string& newRequestStr, std::string* plateStr = nullptr);
	/*
	作用 生成响应并发送
	参数 optCode 对数据库操作的标识码
		 opt 对数据库操作的简述
		 fd 即将接收响应的套接字描述符
		 inData 从请求中解析出来的数据
	*/
	void _createResponse(enum optCode optCode, std::string& opt, int fd,std::string& inData);
	/*
	作用 将响应结构体格式化成响应字符串
	参数 responseStr 格式化后的响应字符串
		 response 响应结构体
	*/
	void _formatResponse(std::string& responseStr, struct response& response);
	/*
	作用 发送响应
	参数 responseStr 要发送的响应字符串
		 fd 发送目标套接字描述符
	*/
	void _sendResponse(std::string& responseStr, int fd);
	/*
	作用 识别车牌
	参数 data 从请求分离的包含图片的json字符串
	     plateStr 用来存放车牌号的字符串
	*/
	bool _recognizePlate(std::string& data, std::string& plateStr);
	/*
	作用 获取车牌识别api返回的数据
	     curl库用于获取响应的回调函数
	参数 ptr 接收到的数据字符串起始地址
		 size 单块长度
		 nmemb 块数量
		 userdata 用户存放数据字符串起始地址
	*/
	static size_t getHttpData(char* ptr, size_t size, size_t nmemb, void* userdata);
	/*
	作用 解析api返回的数据并解析出车牌号
	参数 httpResponse 请求api后获得的响应字符串
		 plateStr 用来存放车牌号的字符串
	*/
	void _analyzePlate(std::string& httpResponse, std::string& plateStr);
	/*
	作用 发送车牌号
	参数 fd 发送目标的套接字描述符
		 plateStr 要发送的车牌号字符串
	*/
	bool _sendPlate(int fd, std::string& plateStr);
};

