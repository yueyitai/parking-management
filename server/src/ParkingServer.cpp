#include "ParkingServer.h"

ParkingServer::ParkingServer(unsigned short serverPort)
	:ClientManager(serverPort)
{
}

ParkingServer::~ParkingServer()
{
}

bool ParkingServer::_handleData(int clientFD)
{
	std::size_t recvSize = 1024 * 1024;
	std::size_t dataSize = 0;
	std::unique_ptr<char[]> recvBuf(new char[recvSize]);
	memset(recvBuf.get(), 0, recvSize);

	std::size_t recvByte = recv(clientFD, &dataSize, sizeof(dataSize), 0);
	if (static_cast<int>(recvByte) == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}
	else if (static_cast<int>(recvByte) == 0)
	{
		log_info("Disconnected: [%s:%hu]", &clients[clientFD].ip[0], clients[clientFD].port);

		clients.erase(clients.find(clientFD));
		log_debug("clients size: %d", clients.size());

		if (!epoll.delEvent(clientFD))
		{
			log_error("%s error", __FUNCTION__);
			return false;
		}

		close(clientFD);
		clientCount--;

		log_debug("%s success", __FUNCTION__);
		return true;
	}

	recvByte = recv(clientFD, recvBuf.get(), dataSize, 0);

	tempData = recvBuf.get();

	clients[clientFD].data = recvBuf.get();
	log_info("Receive data from [%s:%hu], data: %s", &clients[clientFD].ip[0], clients[clientFD].port, &clients[clientFD].data[0]);

	//操作
	_handleRequest(clients[clientFD].data, clientFD);

	log_debug("%s success", __FUNCTION__);
	return true;
}

void ParkingServer::_handleRequest(std::string requestStr, int fd)
{
	struct request request;
	memset(&request, 0, sizeof(request));

	cJSON* jsonRoot = cJSON_Parse(requestStr.c_str());
	cJSON* jsonHeader = cJSON_GetObjectItem(jsonRoot, "header");
	cJSON* jsonBody = cJSON_GetObjectItem(jsonRoot, "body");
	cJSON* jsonOptCode = cJSON_GetObjectItem(jsonHeader, "opt_code");
	cJSON* jsonOpt = cJSON_GetObjectItem(jsonHeader, "opt");
	cJSON* jsonData = cJSON_GetObjectItem(jsonBody, "data");

	request.header.optCode = (enum optCode)jsonOptCode->valueint;
	request.header.opt = jsonOpt->valuestring;
	request.body.data = jsonData->valuestring;

	cJSON_Delete(jsonRoot);

	log_debug("requestType:%hu requestOpt:%s requestData:%s", request.header.optCode, request.header.opt.c_str(), request.body.data.c_str());

	switch (request.header.optCode)
	{
	case ECLIENT_GETALLINFO:
	{
		log_debug("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_GETALLINFO, request.header.opt, fd);

		break;
	}
	case ECLIENT_INSERT_ONE_INFO:
	{
		log_debug("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_INSERT_ONE_INFO, request.header.opt, fd);

		break;
	}
	case ECLIENT_QUERY_ONE_INFO_BY_ID:
	{
		log_debug("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_QUERY_ONE_INFO_BY_ID, request.header.opt, fd);

		break;
	}
	case ECLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		log_debug("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_UPDATE_ONE_INFO_BY_ID, request.header.opt, fd);

		break;
	}
	default:
		break;
	}
}

void ParkingServer::_createResponse(enum optCode optCode, std::string& opt, int fd)
{
	struct response response;

	switch (optCode)
	{
	case ECLIENT_GETALLINFO:
	{
		//数据库接口

		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ECLIENT_GETALLINFO},"haha" };
		break;
	}
	case ECLIENT_INSERT_ONE_INFO:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ECLIENT_INSERT_ONE_INFO},"haha" };
		break;
	}
	case ECLIENT_QUERY_ONE_INFO_BY_ID:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ECLIENT_QUERY_ONE_INFO_BY_ID},"haha" };
		break;
	}
	case ECLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ECLIENT_UPDATE_ONE_INFO_BY_ID},"haha" };
		break;
	}
	default:
		break;
	}

	std::string responseStr;

	_formatResponse(responseStr, response);
	log_info("response:%s", responseStr.c_str());

	_sendResponse(responseStr, fd);
}

void ParkingServer::_formatResponse(std::string& responseStr, struct response& response)
{
	cJSON* jsonRoot = cJSON_CreateObject();
	cJSON* jsonHeader = cJSON_CreateObject();
	cJSON_AddStringToObject(jsonHeader, "result", response.header.result.c_str());
	cJSON_AddNumberToObject(jsonHeader, "result_code", response.header.resultCode);
	cJSON_AddStringToObject(jsonHeader, "opt", response.header.opt.c_str());
	cJSON_AddNumberToObject(jsonHeader, "opt_code", response.header.optCode);
	cJSON_AddItemToObject(jsonRoot, "header", jsonHeader);
	cJSON* jsonBody = cJSON_CreateObject();
	cJSON_AddStringToObject(jsonBody, "data", response.body.data.c_str());
	cJSON_AddItemToObject(jsonRoot, "body", jsonBody);
	char* tempData = cJSON_Print(jsonRoot);
	responseStr = tempData;

	free(tempData);
	cJSON_Delete(jsonRoot);

	log_debug("response:%s", responseStr.c_str());
}

void ParkingServer::_sendResponse(std::string& responseStr, int fd)
{
	size_t responseSize = responseStr.length();

	int ret = send(fd, &responseSize, sizeof(responseSize), 0);
	log_debug("ret:%d,responseSize:%d", ret, responseSize);

	ret = send(fd, responseStr.c_str(), responseSize, 0);
	log_debug("ret:%d", ret);
}
