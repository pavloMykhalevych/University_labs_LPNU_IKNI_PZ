#pragma once

#include "Mailing.h"

#include "Includes.h"

void SharesThread(void* Param);

class Shares : public Mailing
{
	friend void SharesThread(void* Param);
public:
	Shares(int time);

	virtual void SendMailThread() override;
};

