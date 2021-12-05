#include "Weather.h"

Weather::Weather(int time) : Mailing(time) {
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WeatherThread, (void*)this, NULL, NULL);
}

void Weather::SendMailThread() {
	while (true) {
		srand(time(NULL));
		int temp = rand() % 45 - 20;
		int humidity = rand() % 50 + 50;
		double pressure = ((rand() % 300) / 10.0) + 985.;
		std::ostringstream pressureStr;
		pressureStr << std::fixed << std::setprecision(1) << pressure;
		std::string mes = "Weather:\n\tTemperature: " + std::to_string(temp)
			+ " C\n\tHumidity: " + std::to_string(humidity)
			+ " %\n\tPressure: " + pressureStr.str() + " hPA\n";
		SendMail(mes);
		Sleep(m_period);
	}
}

void WeatherThread(void* Param) {
	Weather* This = (Weather*)Param;
	This->SendMailThread();
}