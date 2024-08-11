#pragma once

#include <map>
#include <memory>
#include <thread>

#include "log.h"
#include "Client.h"
#include "Epoll.h"
#include "TcpServer.h"

#define MAX_CLIENT 500

class ClientManager
{
public:
	ClientManager(unsigned short serverPort);
	~ClientManager();
	bool init();
	bool run();

protected:
	bool _init();
	void _run();
	bool _handleNewClient(int clientFD, struct sockaddr_in* info);
	virtual bool _handleData(int clientFD);

protected:
	TcpServer server;
	Epoll epoll;
	std::map<int, Client> clients;
	unsigned short clientCount;
	std::thread thread;
	std::string tempData;
};

