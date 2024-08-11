#include "ParkingServer.h"
#include "base64.h"
#include "adInfomationFormationController.h"
#include "EmployeeInformationFormationController.h"
#include "parkingRecordFormationController.h"
#include "VIPInformationController.h"

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

//处理服务器接收的数据
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

	log_debug("%s success", __FUNCTION__);
	return true;
}

//处理接收到的请求，判断要做什么操作
void ParkingServer::_handleRequest(std::string requestStr, int fd)
{
	struct request request;
	//memset(&request, 0, sizeof(request));

	_analyzeRequest(requestStr, request);

	log_debug("requestOptCode:%hu requestOpt:%s requestData:%s", request.header.optCode, request.header.opt.c_str(), request.body.data.c_str());

	switch (request.header.optCode)
	{
	/*--------------------员工管理系统处理--------------------*/
	//获取全部员工信息
	case ECLIENT_GET_ALL_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());


		_createResponse(ECLIENT_GET_ALL_INFO, request.header.opt, fd,request.body.data);

		break;
	}
	//插入单条员工信息
	case ECLIENT_INSERT_ONE_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_INSERT_ONE_INFO, request.header.opt, fd,request.body.data);

		break;
	}
	//根据id查询单条员工信息
	case ECLIENT_QUERY_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_QUERY_ONE_INFO_BY_ID, request.header.opt, fd,request.body.data);

		break;
	}
	//根据id更新单条员工信息
	case ECLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ECLIENT_UPDATE_ONE_INFO_BY_ID, request.header.opt, fd,request.body.data);

		break;
	}
	/*--------------------广告系统处理--------------------*/
	//插入单条广告信息
	case ADCLIENT_INSERT_ONE_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ADCLIENT_INSERT_ONE_INFO, request.header.opt, fd,request.body.data);

		//处理图片，将图片存到本地
		_handleImage(request.body.data, fd);

		//将request中图片信息改为图片路径
		std::string newRequestStr;
		_changeJsonStr(requestStr, newRequestStr);

		struct request newRequest;
		_analyzeRequest(newRequestStr, newRequest);

		log_debug("newRequest.body.data:%s",newRequest.body.data.c_str());

		//数据库接口
		std::string outData;
		try
		{
			Ad_information_formationDAO dao;
			AdInformationFormationController controller(&dao);
			outData = controller.insertAdInformationFormation(newRequest.body.data);
		}
		catch(const std::exception& e)
		{
			log_error("[ADCLIENT_INSERT_ONE_INFO]ad operate error %s",e.what());
		}
		
		log_debug("outData:%s",outData.c_str());

		break;
	}
	//根据id查询单条广告信息
	case ADCLIENT_QUERY_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ADCLIENT_QUERY_ONE_INFO_BY_ID, request.header.opt, fd,request.body.data);

		break;
	}
	//根据id修改单条广告信息
	case ADCLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ADCLIENT_UPDATE_ONE_INFO_BY_ID, request.header.opt, fd,request.body.data);

		break;
	}
	//根据id删除单条广告信息
	case ADCLIENT_DELETE_ONE_INFO_BY_ID:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ADCLIENT_DELETE_ONE_INFO_BY_ID, request.header.opt, fd,request.body.data);

		break;
	}
	//获取所有广告信息
	case ADCLIENT_GET_ALL_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(ADCLIENT_GET_ALL_INFO, request.header.opt, fd,request.body.data);

		break;
	}
	/*--------------------停车场系统处理--------------------*/
	//根据车牌查询单条信息
	case PCLIENT_QUERY_ONE_INFO_BY_PLATE:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(PCLIENT_QUERY_ONE_INFO_BY_PLATE, request.header.opt, fd,request.body.data);

		break;
	}
	//插入单条停车信息
	case PCLIENT_INSERT_ONE_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(PCLIENT_INSERT_ONE_INFO, request.header.opt, fd,request.body.data);

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
		if(plateStr != "null")
		{
			log_debug("plateStr is not null");
			//将request中图片信息改为图片路径
			std::string newRequestStr;
			_changeJsonStr(requestStr, newRequestStr, &plateStr);

			struct request newRequest;
			_analyzeRequest(newRequestStr, newRequest);

			log_debug("newRequest.data:%s", newRequest.body.data.c_str());

			//数据库接口
			std::string outData;
			try
			{
				ParkingRecordFormationDAO dao;
				ParkingRecordFormationController controller(&dao);
				outData = controller.usePark(newRequest.body.data);
			}
			catch(const std::exception& e)
			{
				log_error("[PCLIENT_INSERT_ONE_INFO]p operate error %s",e.what());
			}

			log_debug("outData:%s",outData.c_str());
		}
		else log_debug("plateStr is null");

		break;
	}
	/*--------------------VIP系统处理--------------------*/
	//插入单条vip信息（注册）
	case VIPCLIENT_INSERT_ONE_INFO:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(VIPCLIENT_INSERT_ONE_INFO, request.header.opt, fd,request.body.data);

		break;
	}
	//根据车牌查询单条vip信息
	case VIPCLIENT_QUERY_ONE_INFO_BY_PLATE:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(VIPCLIENT_QUERY_ONE_INFO_BY_PLATE, request.header.opt, fd,request.body.data);

		break;
	}
	//根据车牌修改单条vip信息
	case VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE:
	{
		log_info("requestOpt:%s", request.header.opt.c_str());

		_createResponse(VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE, request.header.opt, fd,request.body.data);

		break;
	}
	default:
		log_info("requestOpt not found");
		break;
	}
}

//解析请求
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

//接收图片数据并存到本地
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
	std::string imgPath = "./images/" + imgName;

	std::fstream file;
	file.open(imgPath, std::ios_base::out);
	if (!file.is_open())
	{
		log_error("%s open error", imgPath.c_str());
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

//修改请求信息为数据库所需格式
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
		dataObj["image"] = "./images/" + imgName;

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

//生成响应并发送
void ParkingServer::_createResponse(enum optCode optCode, std::string& opt, int fd,std::string& inData)
{
	struct response response;

	switch (optCode)
	{
	//员工
	//获取全部员工信息
	case ECLIENT_GET_ALL_INFO:
	{
		//数据库接口
		std::string outData;
		try
		{
			EmployeeInformationFormationDAO dao;
			EmployeeInformationFormationController controller(&dao);
			outData = controller.getAllEmployee();
		}
		catch(const std::exception& e)
		{
			log_error("[ECLIENT_GET_ALL_INFO]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,ECLIENT_GET_ALL_INFO},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ECLIENT_GET_ALL_INFO},outData };

		break;
	}
	//插入单条员工信息
	case ECLIENT_INSERT_ONE_INFO:
	{
		//数据库接口
		std::string outData;
		try
		{
			EmployeeInformationFormationDAO dao;
			EmployeeInformationFormationController controller(&dao);
			outData = controller.insert(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[ECLIENT_INSERT_ONE_INFO]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,ECLIENT_INSERT_ONE_INFO},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ECLIENT_INSERT_ONE_INFO},outData };

		break;
	}
	//根据id查询单条员工信息
	case ECLIENT_QUERY_ONE_INFO_BY_ID:
	{
		//数据库接口
		std::string outData;
		try
		{
			EmployeeInformationFormationDAO dao;
			EmployeeInformationFormationController controller(&dao);
			outData = controller.searchWithId(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[ECLIENT_QUERY_ONE_INFO_BY_ID]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,ECLIENT_QUERY_ONE_INFO_BY_ID},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ECLIENT_QUERY_ONE_INFO_BY_ID},outData };

		break;
	}
	//根据id更新单条员工信息
	case ECLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		//数据库接口
		std::string outData;
		try
		{
			EmployeeInformationFormationDAO dao;
			EmployeeInformationFormationController controller(&dao);
			outData = controller.updateWithId(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[ECLIENT_UPDATE_ONE_INFO_BY_ID]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,ECLIENT_UPDATE_ONE_INFO_BY_ID},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ECLIENT_UPDATE_ONE_INFO_BY_ID},outData };

		break;
	}
	/*--------------------广告系统处理--------------------*/
	//插入单条广告信息
	case ADCLIENT_INSERT_ONE_INFO:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_INSERT_ONE_INFO},"recv image info success, ready to recv image data" };

		break;
	}
	//根据id查询单条广告信息
	case ADCLIENT_QUERY_ONE_INFO_BY_ID:
	{
		//数据库接口
		std::string outData;
		try
		{
			Ad_information_formationDAO dao;
			AdInformationFormationController controller(&dao);
			outData = controller.selectAdInformationFormationById(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[ADCLIENT_QUERY_ONE_INFO_BY_ID]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,ADCLIENT_QUERY_ONE_INFO_BY_ID},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_QUERY_ONE_INFO_BY_ID},outData };

		break;
	}
	//根据id修改单条广告信息
	case ADCLIENT_UPDATE_ONE_INFO_BY_ID:
	{
		//数据库接口
		std::string outData;
		try
		{
			Ad_information_formationDAO dao;
			AdInformationFormationController controller(&dao);
			outData = controller.updateAdInformationFormationById(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[ADCLIENT_UPDATE_ONE_INFO_BY_ID]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,ADCLIENT_UPDATE_ONE_INFO_BY_ID},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_UPDATE_ONE_INFO_BY_ID},outData };

		break;
	}
	//根据id删除单条广告信息
	case ADCLIENT_DELETE_ONE_INFO_BY_ID:
	{
		log_debug("inData:%s",inData.c_str());

		//数据库接口
		std::string outData;
		try
		{
			Ad_information_formationDAO dao;
			AdInformationFormationController controller(&dao);
			outData = controller.deleteAdInformationFormationById(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[ADCLIENT_DELETE_ONE_INFO_BY_ID]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,ADCLIENT_DELETE_ONE_INFO_BY_ID},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_DELETE_ONE_INFO_BY_ID},outData };

		break;
	}
	//获取所有广告信息
	case ADCLIENT_GET_ALL_INFO:
	{
		//数据库接口
		std::string outData;
		try
		{
			Ad_information_formationDAO dao;
			AdInformationFormationController controller(&dao);
			outData = controller.getAllAdInformationFormation();
		}
		catch(const std::exception& e)
		{
			log_error("[ADCLIENT_GET_ALL_INFO]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,ADCLIENT_GET_ALL_INFO},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,ADCLIENT_GET_ALL_INFO},outData };

		break;
	}
	/*--------------------停车场系统处理--------------------*/
	//根据车牌查询单条信息
	case PCLIENT_QUERY_ONE_INFO_BY_PLATE:
	{
		//数据库接口
		std::string outData;
		try
		{
			ParkingRecordFormationDAO dao;
			ParkingRecordFormationController controller(&dao);
			outData = controller.searchWithPlate(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[PCLIENT_QUERY_ONE_INFO_BY_PLATE]e operate error %s",e.what());
		}

		log_debug("outData:%s",outData.c_str());
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,PCLIENT_QUERY_ONE_INFO_BY_PLATE},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,PCLIENT_QUERY_ONE_INFO_BY_PLATE},outData };

		break;
	}
	//插入单条停车信息
	case PCLIENT_INSERT_ONE_INFO:
	{
		response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,PCLIENT_INSERT_ONE_INFO},"recv image info success, ready to recv image data" };

		break;
	}
	/*--------------------VIP系统处理--------------------*/
	//插入单条vip信息
	case VIPCLIENT_INSERT_ONE_INFO:
	{
		//数据库接口
		std::string outData;
		try
		{
			VIPInformationDAO dao;
			VIPInformationController controller(&dao);
			outData = controller.VIPRegister(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[VIPCLIENT_INSERT_ONE_INFO]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,VIPCLIENT_INSERT_ONE_INFO},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,VIPCLIENT_INSERT_ONE_INFO},outData };

		break;
	}
	//根据车牌查询单条vip信息
	case VIPCLIENT_QUERY_ONE_INFO_BY_PLATE:
	{
		//数据库接口
		std::string outData;
		try
		{
			VIPInformationDAO dao;
			VIPInformationController controller(&dao);
			outData = controller.VIPLogin(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[VIPCLIENT_QUERY_ONE_INFO_BY_PLATE]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,VIPCLIENT_QUERY_ONE_INFO_BY_PLATE},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,VIPCLIENT_QUERY_ONE_INFO_BY_PLATE},outData };

		break;
	}
	//根据车牌修改单条vip信息
	case VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE:
	{
		//数据库接口
		std::string outData;
		try
		{
			VIPInformationDAO dao;
			VIPInformationController controller(&dao);
			outData = controller.VIPCharge(inData);
		}
		catch(const std::exception& e)
		{
			log_error("[VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE]e operate error %s",e.what());
		}
		
		if(outData == "FAIL") response = { {"FAIL",RESPONSE_RESULT_FAIL,opt,VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE},outData };
		else response = { {"SUCCESS",RESPONSE_RESULT_SUCCESS,opt,VIPCLIENT_UPDATE_ONE_INFO_BY_PLATE},outData };

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

//将响应结构体格式化成响应字符串
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

	//log_debug("response:%s", responseStr.c_str());
}

//发送响应
void ParkingServer::_sendResponse(std::string& responseStr, int fd)
{
	size_t responseSize = responseStr.length();

	int ret = send(fd, &responseSize, sizeof(responseSize), 0);
	log_debug("ret:%d,responseSize:%d", ret, responseSize);

	ret = send(fd, responseStr.c_str(), responseSize, 0);
	log_debug("ret:%d", ret);
}

//识别车牌
bool ParkingServer::_recognizePlate(std::string& data,std::string& plateStr)
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

	std::string filePath = "./images/" + imgName;
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

	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	//log_debug("data:%s", httpData.c_str());

	_analyzePlate(httpData, plateStr);

	log_debug("%s success",__FUNCTION__);
	return true;
}

//获取车牌识别api返回的数据
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

//解析api返回的数据并解析出车牌号
void ParkingServer::_analyzePlate(std::string& httpResponse, std::string& plateStr)
{
	std::string responseJson = httpResponse.substr(httpResponse.find('{'));
	log_debug("responseJson:%s", responseJson.c_str());

	try
	{
		using json = nlohmann::json;
		json j = json::parse(responseJson);
		plateStr = j["words_result"]["number"];
	}
	catch (const std::exception& e)
	{
		log_error("json parse error %s", e.what());
		plateStr = "null";
	}

	log_debug("%s finished", __FUNCTION__);
}

//发送车牌号
bool ParkingServer::_sendPlate(int fd, std::string& plateStr)
{
	size_t strlen = plateStr.length();
	int ret = send(fd, &strlen, sizeof(strlen), 0);
	log_debug("ret:%d", ret);
	if (ret < 0)
	{
		log_error("send plateStr len error");
		return false;
	}

	ret = send(fd, plateStr.c_str(), strlen, 0);
	log_debug("ret:%d", ret);
	if (ret < 0)
	{
		log_error("send plateStr len error");
		return false;
	}

	log_info("send plate success");
	return true;
}