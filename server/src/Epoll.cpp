#include "Epoll.h"

Epoll::Epoll(unsigned short maxClient)
	:size(maxClient)
{
	memset(&event, 0, sizeof(event));
	eventSet = new struct epoll_event[size];

}

Epoll::~Epoll()
{
	delete[]eventSet;
	close(fd);
}

bool Epoll::init(int serverFD)
{
	return _init(serverFD);
}

bool Epoll::_init(int serverFD)
{
	fd = epoll_create(size);
	if (fd == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	if (!addEvent(serverFD, EPOLLIN))
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool Epoll::addEvent(int addFD, enum EPOLL_EVENTS type)
{
	event.events = type;
	event.data.fd = addFD;

	int ret = epoll_ctl(fd, EPOLL_CTL_ADD, addFD, &event);
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

bool Epoll::delEvent(int delFD)
{
	int ret = epoll_ctl(fd, EPOLL_CTL_DEL, delFD, &event);
	if (ret == -1)
	{
		log_error("%s error", __FUNCTION__);
		return false;
	}

	log_debug("%s success", __FUNCTION__);
	return true;
}

void Epoll::clearEventSet()
{
	memset(eventSet, 0, sizeof(struct epoll_event) * size);
}

int Epoll::epollWait()
{
	return epoll_wait(fd, eventSet, size, 60000);	//60s;
}

epoll_event Epoll::getEvent()
{
	return event;
}

epoll_event* Epoll::getEventSet()
{
	return eventSet;
}
