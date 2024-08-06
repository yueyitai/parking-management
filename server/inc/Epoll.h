#pragma once

#include <cstring>
#include <sys/epoll.h>
#include <unistd.h>

#include "log.h"

class Epoll
{
public:
	Epoll() {};
	Epoll(unsigned short maxClient);
	~Epoll();
	bool init(int serverFD);
	bool addEvent(int addFD, enum EPOLL_EVENTS type);
	bool delEvent(int delFD);
	void clearEventSet();
	int epollWait();
	struct epoll_event getEvent();
	struct epoll_event* getEventSet();

private:
	bool _init(int serverFD);

private:
	int fd;
	struct epoll_event event;
	struct epoll_event* eventSet;
	unsigned short size;
};

