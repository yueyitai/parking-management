#include "EClient.h"
#include "cJSON.h"
#include "log.h"

#include <string.h>
#include <memory>

#define SERVER_IP "192.168.52.128"
#define SERVER_PORT 20202

EClient::EClient()
	:TcpClient(SERVER_IP, SERVER_PORT)
{
}

EClient::~EClient()
{
}

bool EClient::operateDatabase(enum optCode optCode, char* recvBuf, const char* data)
{
	struct request request;

	switch (optCode)
	{
	case ECLIENT_GETALLINFO:
	{
		request = { { ECLIENT_GETALLINFO ,"EClientGetAllInfo" }, "null" };
		break;
	}
	case ECLIENT_INSERT_ONE_INFO:
	{
		request = { { ECLIENT_INSERT_ONE_INFO ,"EClientInsertOneInfo" }, data };
		break;
	}
	case ECLIENT_QUERY_ONE_INFO_BY_ID:
	{
		request = { { ECLIENT_QUERY_ONE_INFO_BY_ID ,"EClientQueryOneInfoById" }, "null" };
		break;
	}
	case ECLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		request = { { ECLIENT_UPDATE_ONE_INFO_BY_ID ,"EClientUpdateOneInfoById" }, data };
		break;
	}
	default:
		break;
	}

	std::string requestStr;

	_formatRequest(requestStr, request);
	log_info("request:%s", requestStr.c_str());

	if (!_sendRequest(requestStr)) return false;

	std::string responseStr;

	if (!_recvResponse(responseStr)) return false;

	struct response response;
	memset(&response, 0, sizeof(response));

	_analyzeResponse(responseStr, response);

	switch (response.header.resultCode)
	{
	case RESPONSE_RESULT_SUCCESS:
	{
		if (recvBuf != nullptr) strcpy(recvBuf, response.body.data.c_str());
		return true;
		break;
	}
	case RESPONSE_RESULT_FAIL:
	{
		return false;
	}
	default:
		break;
	}

	return false;
}

void EClient::_formatRequest(std::string& requestStr, struct request& request)
{
	cJSON* jsonRoot = cJSON_CreateObject();
	cJSON* jsonHeader = cJSON_CreateObject();
	cJSON_AddStringToObject(jsonHeader, "opt", request.header.opt.c_str());
	cJSON_AddNumberToObject(jsonHeader, "opt_code", request.header.optCode);
	cJSON_AddItemToObject(jsonRoot, "header", jsonHeader);
	cJSON* jsonBody = cJSON_CreateObject();
	cJSON_AddStringToObject(jsonBody, "data", request.body.data.c_str());
	cJSON_AddItemToObject(jsonRoot, "body", jsonBody);
	std::unique_ptr<char> tempData(cJSON_Print(jsonRoot));
	requestStr = tempData.get();

	cJSON_Delete(jsonRoot);

	log_debug("request:%s", requestStr.c_str());
}

bool EClient::_sendRequest(std::string& requestStr)
{
	size_t requestSize = strlen(requestStr.c_str());
	log_debug("dataSize:%d", requestSize);

	if (!_send(&requestSize, sizeof(requestSize)))
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}
	if (!_send(requestStr.c_str()))
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

void EClient::_analyzeResponse(std::string& responseStr,struct response& response)
{
	cJSON* jsonRoot = cJSON_Parse(responseStr.c_str());
	cJSON* jsonHeader = cJSON_GetObjectItem(jsonRoot, "header");
	cJSON* jsonBody = cJSON_GetObjectItem(jsonRoot, "body");
	cJSON* jsonResult = cJSON_GetObjectItem(jsonHeader, "result");
	cJSON* jsonResultCode = cJSON_GetObjectItem(jsonHeader, "result_code");
	cJSON* jsonOpt = cJSON_GetObjectItem(jsonHeader, "opt");
	cJSON* jsonOptCode = cJSON_GetObjectItem(jsonHeader, "opt_code");
	cJSON* jsonData = cJSON_GetObjectItem(jsonBody, "data");

	response.header.result = jsonResult->valuestring;
	response.header.resultCode = (enum responseResultCode)jsonResultCode->valueint;
	response.header.opt = jsonOpt->valuestring;
	response.header.optCode = (enum optCode)jsonOptCode->valueint;
	response.body.data = jsonData->valuestring;

	cJSON_Delete(jsonRoot);

	log_debug("result:%s resultCode:%d opt:%s data:%s"
		, response.header.result.c_str()
		, response.header.resultCode
		, response.header.opt.c_str()
		, response.body.data.c_str());
}

bool EClient::_recvResponse(std::string& responseStr)
{
	size_t responseSize;

	if (!_recv(&responseSize, sizeof(responseSize)))
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	std::unique_ptr<char[]> responseBuf(new char[responseSize + 1]);

	if (!_recv(responseBuf.get(), responseSize))
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	responseStr = responseBuf.get();
	log_info("response:%s", responseStr.c_str());

	log_debug("%s success", __FUNCTION__);
	return true;
}
