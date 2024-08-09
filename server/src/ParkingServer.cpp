#include "ParkingServer.h"
#include "base64.h"
#include "controller/adInfomationFormationController.h"
#include "ad_information_formationDAO.h"
#include <memory>

#include <thread>
#include <nlohmann/json.hpp>
#include <fstream>
#include <curl/curl.h>

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
	log_info("Receive data from [%s:%hu], len:%ld data: %s", &clients[clientFD].ip[0], clients[clientFD].port,strlen(clients[clientFD].data.c_str()), &clients[clientFD].data[0]);

	//操作
	try
	{
		std::thread thread = std::thread([&, this] {this->_handleRequest(clients[clientFD].data, clientFD); });

		if (thread.joinable()) thread.join();
	}
	catch (const std::exception& e)
	{
		log_error("handle request thread error %s", e.what());
	}

	//while (true)
	//{
	//	sleep(5);
	//}

	log_debug("%s success", __FUNCTION__);
	return true;
}

void ParkingServer::_handleRequest(std::string requestStr, int fd)
{
	struct request request;
	//memset(&request, 0, sizeof(request));

	_analyzeRequest(requestStr, request);

	log_debug("requestOptCode:%hu requestOpt:%s requestData:%s", request.header.optCode, request.header.opt.c_str(), request.body.data.c_str());

	switch (request.header.optCode)
	{
	//员工管理系统处理
	case ECLIENT_GET_ALL_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_GET_ALL_INFO, request.header.opt, fd);

		break;
	}
	case ECLIENT_INSERT_ONE_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_INSERT_ONE_INFO, request.header.opt, fd);

		break;
	}
	case ECLIENT_QUERY_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_QUERY_ONE_INFO_BY_ID, request.header.opt, fd);

		break;
	}
	case ECLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_UPDATE_ONE_INFO_BY_ID, request.header.opt, fd);

		break;
	}
	//广告系统处理
	case ADCLIENT_INSERT_ONE_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		try
		{
			//操作数据库
			Ad_information_formationDAO dao;
			AdInformationFormationController controller(&dao);
			controller.insertAdInformationFormation(request.body.data);
		}
		catch (const std::exception& e)
		{
			log_error("ad operate database error %s", e.what());
		}

		_createResponse(ADCLIENT_INSERT_ONE_INFO, request.header.opt, fd);

		//处理图片，将图片存到本地
		_handleImage(request.body.data, fd);

		//将request中图片信息改为图片路径
		std::string newRequestStr;
		_changeJsonStr(requestStr, newRequestStr);

		break;
	}
	case ADCLIENT_QUERY_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ADCLIENT_QUERY_ONE_INFO_BY_ID, request.header.opt, fd);

		break;
	}
	case ADCLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_UPDATE_ONE_INFO_BY_ID, request.header.opt, fd);

		break;
	}
	case ADCLIENT_DELETE_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ADCLIENT_DELETE_ONE_INFO_BY_ID, request.header.opt, fd);

		break;
	}
	case ADCLIENT_GET_ALL_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ADCLIENT_GET_ALL_INFO, request.header.opt, fd);

		break;
	}
	//停车场系统处理
	case PCLIENT_QUERY_ONE_INFO_BY_PLATE:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(PCLIENT_QUERY_ONE_INFO_BY_PLATE, request.header.opt, fd);

		break;
	}
	case PCLIENT_INSERT_ONE_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(PCLIENT_INSERT_ONE_INFO, request.header.opt, fd);

		//处理图片
		_handleImage(request.body.data, fd);
#if 1
		//请求车牌识别api
		std::string plateStr;
		if (!_recognizePlate(request.body.data, plateStr)) log_error("recognize plate error");
		log_info("plateJsonStr: %s", plateStr.c_str());

		//发送车牌
		if (!_sendPlate(fd, plateStr)) log_debug("send plate error");
#endif
		//将request中图片信息改为图片路径
		std::string newRequestStr;
		_changeJsonStr(requestStr, newRequestStr, &plateStr);

		struct request newRequest;
		_analyzeRequest(newRequestStr, newRequest);

		log_debug("newRequest.data:%s", newRequest.body.data.c_str());

		break;
	}
	case PCLIENT_DELETE_ONE_INFO_BY_PLATE:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(PCLIENT_DELETE_ONE_INFO_BY_PLATE, request.header.opt, fd);

		break;
	}
	case PCLIENT_QUERY_PLATE_EXISTENCE_IN_EMPLOYEE_TABLE_BY_PLATE:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(PCLIENT_QUERY_PLATE_EXISTENCE_IN_EMPLOYEE_TABLE_BY_PLATE, request.header.opt, fd);

		break;
	}
	case PCLIENT_QUERY_PLATE_EXISTENCE_IN_VIP_TABLE_BY_PLATE:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(PCLIENT_QUERY_PLATE_EXISTENCE_IN_VIP_TABLE_BY_PLATE, request.header.opt, fd);

		break;
	}
	//VIP系统处理
	case VIPCLIENT_INSERT_ONE_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(VIPCLIENT_INSERT_ONE_INFO, request.header.opt, fd);

		break;
	}
	case VIPCLIENT_QUERY_ONE_INFO_BY_PLATE:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(VIPCLIENT_QUERY_ONE_INFO_BY_PLATE, request.header.opt, fd);

		break;
	}
	case VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE, request.header.opt, fd);

		break;
	}
	default:
		log_info("requestOpt not found");
		break;
	}
}

void ParkingServer::_analyzeRequest(std::string& requestStr, request& request)
{
	/*-----nlohmannJson-----*/
	using json = nlohmann::json;
	try {
		json j = json::parse(requestStr);

		request.header.optCode = j["header"]["opt_code"];
		request.header.opt = j["header"]["opt"];
		request.body.data = j["body"]["data"];
	}
	catch (std::exception& e) {
		log_error("json parse error %s", e.what());
	}

	log_debug("_analyzeRequest finished");
}

void ParkingServer::_handleImage(std::string data,int fd)
{
	std::string imgName;
	size_t imgSize;

	using json = nlohmann::json;
	try
	{
		json j = json::parse(data);

		imgName = j["image"]["name"];
		imgSize = j["image"]["size"];
	}
	catch (const std::exception& e)
	{
		log_error("json parse error %s",e.what());
	}

	log_debug("imgName:%s,imgSize:%d", imgName.c_str(), imgSize);

#if 1
	std::fstream file;
	file.open(imgName, std::ios_base::out);
	if (!file.is_open())
	{
		log_error("%s open error", imgName.c_str());
		return;
	}

	int ret = -1;
	size_t tempSize = 0;
	while (true)
	{
		if (tempSize >= imgSize || ret == 0)
		{
			log_info("recv image finished");
			break;
		}

		char buf[1024 * 10] = { 0 };
		ret = recv(fd, buf, 1024 * 10, 0);
		if (ret < 0)
		{
			log_error("recv data error");
			break;
		}
		log_debug("ret = %d", ret);

		file.write(buf, ret);

		tempSize += ret;
		log_debug("tempSize:%d", tempSize);
	}

	file.close();
#endif

	log_debug("_handleImage finished");
}

void ParkingServer::_changeJsonStr(std::string& baseRequestStr, std::string& newRequestStr,std::string* plateStr)
{
	log_debug("baseRequest:%s", baseRequestStr.c_str());

	try
	{
		using json = nlohmann::json;

		json j = json::parse(baseRequestStr);
		std::string dataStr = j["body"]["data"];
		json dataObj = json::parse(dataStr);
		std::string imgName = dataObj["image"]["name"];
		dataObj.erase("image");
		dataObj["image"] = imgName;

		if (plateStr != nullptr)
		{
			dataObj["licence_plate"] = *plateStr;
		}

		j["body"]["data"] = dataObj.dump();

		newRequestStr = j.dump();
	}
	catch (const std::exception& e)
	{
		log_error("json parse error %s", e.what());
	}

	log_debug("newRequestStr:%s", newRequestStr.c_str());
}

void ParkingServer::_createResponse(enum optCode optCode, std::string& opt, int fd)
{
	struct response response;

	switch (optCode)
	{
	//员工
	case ECLIENT_GET_ALL_INFO:
	{
		//数据库接口

		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ECLIENT_GET_ALL_INFO},"haha" };
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
	//广告
	case ADCLIENT_INSERT_ONE_INFO:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_INSERT_ONE_INFO},"haha" };
		break;
	}
	case ADCLIENT_QUERY_ONE_INFO_BY_ID:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_QUERY_ONE_INFO_BY_ID},"haha" };
		break;
	}
	case ADCLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_UPDATE_ONE_INFO_BY_ID},"haha" };
		break;
	}
	case ADCLIENT_DELETE_ONE_INFO_BY_ID:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_DELETE_ONE_INFO_BY_ID},"haha" };
		break;
	}
	case ADCLIENT_GET_ALL_INFO:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_GET_ALL_INFO},"haha" };
		break;
	}
	//停车场
	case PCLIENT_QUERY_ONE_INFO_BY_PLATE:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,PCLIENT_QUERY_ONE_INFO_BY_PLATE},"haha" };
		break;
	}
	case PCLIENT_INSERT_ONE_INFO:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,PCLIENT_INSERT_ONE_INFO},"haha" };
		break;
	}
	case PCLIENT_DELETE_ONE_INFO_BY_PLATE:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,PCLIENT_DELETE_ONE_INFO_BY_PLATE},"haha" };
		break;
	}
	case PCLIENT_QUERY_PLATE_EXISTENCE_IN_EMPLOYEE_TABLE_BY_PLATE:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,PCLIENT_QUERY_PLATE_EXISTENCE_IN_EMPLOYEE_TABLE_BY_PLATE},"haha" };
		break;
	}
	case PCLIENT_QUERY_PLATE_EXISTENCE_IN_VIP_TABLE_BY_PLATE:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,PCLIENT_QUERY_PLATE_EXISTENCE_IN_VIP_TABLE_BY_PLATE},"haha" };
		break;
	}
	//VIP
	case VIPCLIENT_INSERT_ONE_INFO:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,VIPCLIENT_INSERT_ONE_INFO},"haha" };
		break;
	}
	case VIPCLIENT_QUERY_ONE_INFO_BY_PLATE:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,VIPCLIENT_QUERY_ONE_INFO_BY_PLATE},"haha" };
		break;
	}
	case VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE},"haha" };
		break;
	}
	default:
		break;
	}

	std::string responseStr;

	_formatResponse(responseStr, response);
	log_info("response:%s for optCode:%d", responseStr.c_str(),response.header.optCode);

	_sendResponse(responseStr, fd);
}

void ParkingServer::_formatResponse(std::string& responseStr, struct response& response)
{
	try
	{
		using json = nlohmann::json;

		json j;
		j["header"]["result"] = response.header.result;
		j["header"]["result_code"] = response.header.resultCode;
		j["header"]["opt"] = response.header.opt;
		j["header"]["opt_code"] = response.header.optCode;
		j["body"]["data"] = response.body.data;

		responseStr = j.dump();
	}
	catch (const std::exception& e)
	{
		log_error("json generate error %s", e.what());
	}

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

bool ParkingServer::_recognizePlate(std::string& data,std::string& plateJsonStr)
{
	log_debug("data:%s", data.c_str());

	std::string imgName;
	try
	{
		using json = nlohmann::json;
		json j = json::parse(data);
		imgName = j["image"]["name"];
	}
	catch (const std::exception& e)
	{
		log_error("json parse error %s", e.what());
	}

	log_debug("imgName:%s", imgName.c_str());

	std::string filePath = "./" + imgName;
	log_debug("filePath:%s", filePath.c_str());

	std::string imgBase64 = getFileBase64Content(filePath.c_str());
	//log_debug("imgBase64:%s", imgBase64.c_str());
	std::string imgUrlEncoded = base64_to_url_encoded(imgBase64);
	//log_debug("imgUrlEncoded:%s", imgUrlEncoded.c_str());

	CURL* curl = curl_easy_init();
	if (!curl) 
	{
		log_error("curl error");
		return false;
	}

	std::string url = "https://aip.baidubce.com/rest/2.0/ocr/v1/license_plate";
	std::string token = "?access_token=24.c2fc0a6994889afc448df60b48767599.2592000.1725019619.282335-101196314";
	url += token;
	std::string body = "image=" + imgUrlEncoded;
	curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "Content-Type:application/x-www-form-urlencoded");
	headers = curl_slist_append(headers, "Accept:application/json");

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_HEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getHttpData);
	std::string httpData;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		log_error("Curl perform error: %s", curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		return false;
	}

	curl_easy_cleanup(curl);

	//log_debug("data:%s", httpData.c_str());

	_analyzePlate(httpData, plateJsonStr);

	log_debug("%s success",__FUNCTION__);
	return true;
}

size_t ParkingServer::getHttpData(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	// userdata 应该是一个指向 std::string 的指针
	std::string* httpData = static_cast<std::string*>(userdata);

	// 计算实际接收到的数据长度
	size_t dataSize = size * nmemb;

	// 将数据追加到 httpData 字符串中
	httpData->append(static_cast<char*>(ptr), dataSize);

	// 返回接收到的数据长度
	return dataSize;
}

void ParkingServer::_analyzePlate(std::string& httpResponse, std::string& plateJsonStr)
{
	std::string responseJson = httpResponse.substr(httpResponse.find('{'));
	log_debug("responseJson:%s", responseJson.c_str());

	try
	{
		using json = nlohmann::json;
		json j = json::parse(responseJson);
		plateJsonStr = j["words_result"]["number"];
	}
	catch (const std::exception& e)
	{
		log_error("json parse error %s", e.what());
	}

	log_debug("%s finished", __FUNCTION__);
}

bool ParkingServer::_sendPlate(int fd, std::string& plateJsonStr)
{
	size_t strlen = plateJsonStr.length();
	int ret = send(fd, &strlen, sizeof(strlen), 0);
	log_debug("ret:%d", ret);
	if (ret < 0)
	{
		log_error("send plateJsonStr len error");
		return false;
	}

	ret = send(fd, plateJsonStr.c_str(), strlen, 0);
	log_debug("ret:%d", ret);
	if (ret < 0)
	{
		log_error("send plateJsonStr len error");
		return false;
	}

	log_info("send plate success");
	return true;
}