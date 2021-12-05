#pragma once

#include "Includes.h"

class Mailing
{
public:
	Mailing(int time);

	std::string Delete(SOCKET connection);

	bool Find(SOCKET connection);

	void AddSubscribed(SOCKET newClient);

	virtual void SendMailThread() = 0;

	void SendMail(std::string mes);
protected:
	int m_period;

	std::unordered_set<SOCKET> m_subscribed;
};

