#pragma once

#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "log.h"

class TcpServer
{
public:
	TcpServer(unsigned short TcpServerPort);
	~TcpServer();
	bool t_init();
	int t_accept(struct sockaddr_in* info);
	int t_getFD();
	unsigned short t_getPort();

private:
	bool _init();
	bool _socket();
	bool _reuse();
	bool _bind();
	bool _listen();
	int _accept(struct sockaddr_in* info);

private:
	int fd;
	unsigned short port;
};

