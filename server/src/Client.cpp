#include "Client.h"

Client::Client(int clientFD, std::string clientIP, unsigned short clientPort)
	:fd(clientFD), ip(clientIP), port(clientPort)
{
	//log_debug("%s", __FUNCTION__);
}

Client::~Client()
{
	//log_debug("%s", __FUNCTION__);
}
