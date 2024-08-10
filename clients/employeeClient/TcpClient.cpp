#include "TcpClient.h"
#include "log.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

TcpClient::TcpClient(std::string serverIP,unsigned short serverPort)
	:serverIP(serverIP),serverPort(serverPort)
{
	_init();
}

TcpClient::~TcpClient()
{
}

bool TcpClient::_init()
{
	while (true)
	{
		if (!_socket()) break;
		if (!_reuse()) break;
		if (!_connect()) break;

		log_debug("%s success", __FUNCTION__);
		return true;
	}

	log_error("%s error", __FUNCTION__);
	return false;
}

bool TcpClient::_socket()
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool TcpClient::_reuse()
{
	int opt = 1;

	int ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool TcpClient::_connect()
{
	struct sockaddr_in serverAddr;
	memset(&serverAddr,0,sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(&serverIP[0]);
	serverAddr.sin_port = htons(serverPort);

	int ret = connect(fd,(sockaddr*)&serverAddr,sizeof(serverAddr));
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool TcpClient::_send(const char* data)
{
	int ret = send(fd, data, strlen(data), 0);
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success, %d bytes have been sent", __FUNCTION__, ret);
	return true;
}

bool TcpClient::_send(size_t* dataSize, size_t len)
{
	int ret = send(fd, dataSize, len, 0);
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success, %d bytes have been sent", __FUNCTION__, ret);
	return true;
}

bool TcpClient::_recv(char* buf,size_t recvSize)
{
	int ret = recv(fd, buf, recvSize, 0);
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success, %d bytes have been received", __FUNCTION__, ret);
	return true;
}

bool TcpClient::_recv(size_t* dataSize, size_t len)
{
	int ret = recv(fd, dataSize, len, 0);
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success, %d bytes have been received", __FUNCTION__, ret);
	return true;
}
