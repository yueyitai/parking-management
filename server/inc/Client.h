#pragma once

#include <string>

#include "log.h"

class Client
{
public:
	Client() {};
	Client(int clientFD, std::string clientIP, unsigned short clientPort);
	~Client();

public:
	int fd;
	std::string ip;
	unsigned short port;
	std::string data;
};

