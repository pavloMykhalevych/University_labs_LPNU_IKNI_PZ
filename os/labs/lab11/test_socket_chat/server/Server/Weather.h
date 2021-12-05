#pragma once

#include "Mailing.h"

#include "Includes.h"

void WeatherThread(void* Param);

class Weather : public Mailing
{
	friend void WeatherThread(void* Param);
public:
	Weather(int time);

	virtual void SendMailThread() override;
};

