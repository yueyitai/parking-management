#include "TcpServer.h"

int TcpServer::t_accept(struct sockaddr_in* info)
{
	return _accept(info);
}

int TcpServer::t_getFD()
{
	return fd;
}

unsigned short TcpServer::t_getPort()
{
	return port;
}

TcpServer::TcpServer(unsigned short TcpServerPort)
	:port(TcpServerPort)
{
}

bool TcpServer::t_init()
{
	while (true)
	{
		if (!_init()) break;

		log_debug("%s success", __FUNCTION__);
		return true;
	}

	log_error("%s error", __FUNCTION__);
	return false;
}

TcpServer::~TcpServer()
{
	close(fd);
	log_info("Closing TcpServer on %d", port);
}

bool TcpServer::_init()
{
	while (true)
	{
		if (!_socket()) break;
		if (!_reuse()) break;
		if (!_bind()) break;
		if (!_listen()) break;

		log_debug("%s success", __FUNCTION__);
		return true;
	}

	log_error("%s error", __FUNCTION__);
	return false;
}

bool TcpServer::_socket()
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		log_error("%s error",__FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool TcpServer::_reuse()
{
	int opt = 1;

	int ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (ret == -1)
	{
		log_error("%s error",__FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool TcpServer::_bind()
{
	struct sockaddr_in addr_TcpServer;
	memset(&addr_TcpServer, 0, sizeof(addr_TcpServer));

	addr_TcpServer.sin_family = AF_INET;
	addr_TcpServer.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_TcpServer.sin_port = htons(port);

	int ret = bind(fd, reinterpret_cast<struct sockaddr*>(&addr_TcpServer), sizeof(addr_TcpServer));
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool TcpServer::_listen()
{
	int ret = listen(fd, 10);
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

int TcpServer::_accept(struct sockaddr_in* info)
{
	int len = sizeof(*info);

	int clientFD = accept(fd, reinterpret_cast<sockaddr*>(info), reinterpret_cast <socklen_t*>(&len));
	if (clientFD == -1)
	{
		log_error("%s error", __FUNCTION__);
		return -1;
	}

	return clientFD;
}
