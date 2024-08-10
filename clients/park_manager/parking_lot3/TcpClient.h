#pragma once
#include <iostream>

class TcpClient
{
public:
	TcpClient(std::string serverIP, unsigned short serverPort);
	~TcpClient();

private:
	bool _init();
	bool _socket();
	bool _reuse();
	bool _connect();

protected:
	bool _send(const char* data);
	bool _send(size_t* dataSize, size_t len);
	bool _recv(char* buf, size_t recvSize);
	bool _recv(size_t* dataSize, size_t len);

private:
	int fd;
	std::string serverIP;
	unsigned short serverPort;
};

