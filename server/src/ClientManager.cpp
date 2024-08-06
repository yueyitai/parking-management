#include "ClientManager.h"

ClientManager::ClientManager(unsigned short serverPort)
	:server(serverPort), epoll(MAX_CLIENT), clientCount(0)
{
}

ClientManager::~ClientManager()
{
}

bool ClientManager::init()
{
	if (!_init())
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool ClientManager::run()
{
	/*if (!_run())
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;*/

	thread = std::thread([this] {this->_run(); });

	return true;
}

void ClientManager::_run()
{
	log_info("Running TcpServer on %d", server.t_getPort());

	while (true)
	{
		log_debug("clientCount:%d", clientCount);
		if (clientCount > MAX_CLIENT)
		{
			log_error("Connection reached limit");
			return ;
		}

		static int timer = 0;
		epoll.clearEventSet();

		int response = epoll.epollWait();
		if (response == -1)
		{
			log_error("%s error", __FUNCTION__);
			return ;
		}
		else if (response == 0)
		{
			timer++;
			log_info("No connections in %d minute\n", timer);
			continue;
		}

		timer = 0;
		log_debug("[%d]response:%d", server.t_getPort(), response);

		for (int i = 0; i < response; i++)
		{
			if (epoll.getEventSet()[i].events == EPOLLIN)
			{
				if (epoll.getEventSet()[i].data.fd == server.t_getFD())
				{
					struct sockaddr_in clientAddr;
					memset(&clientAddr, 0, sizeof(clientAddr));

					int clientFD = server.t_accept(&clientAddr);
					if (clientFD == -1)
					{
						log_error("%s error", __FUNCTION__);
						return ;
					}

					if (!_handleNewClient(clientFD, &clientAddr))
					{
						log_error("%s error", __FUNCTION__);
						return ;
					}

					if (!epoll.addEvent(clientFD, EPOLLIN))
					{
						log_error("%s error", __FUNCTION__);
						return ;
					}
				}
				else
				{
					int clientFD = epoll.getEventSet()[i].data.fd;

					if (!_handleData(clientFD))
					{
						log_error("%s error", __FUNCTION__);
						return ;
					}
				}
			}
		}
	}
}

bool ClientManager::_init()
{
	if (!server.t_init())
	{
		log_error("Init TcpServer error");
		return false;
	}

	if (!epoll.init(server.t_getFD()))
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool ClientManager::_handleNewClient(int clientFD, struct sockaddr_in* info)
{
	int key = clientFD;
	Client newClient(clientFD, inet_ntoa(info->sin_addr), ntohs(info->sin_port));

	auto [it,success] =  clients.insert({ key,newClient });

	log_info("New client: [%s:%hu]", &newClient.ip[0], newClient.port);
	log_debug("clients size: %d", clients.size());

	clientCount++;

	return success;
}

bool ClientManager::_handleData(int clientFD)
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
	
	log_debug("%s success", __FUNCTION__);
	return true;
}
