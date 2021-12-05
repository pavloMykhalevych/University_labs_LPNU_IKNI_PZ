#include "Shares.h"

Shares::Shares(int time) : Mailing(time) {
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SharesThread, (void*)this, NULL, NULL);
}

void Shares::SendMailThread() {
	while (true) {
		srand(time(NULL));
		double apple = ((rand() % 300) / 100.) + 161.6;
		std::ostringstream appleStr;
		appleStr << std::fixed << std::setprecision(2) << apple;
		double microsoft = ((rand() % 700) / 100.) + 323.2;
		std::ostringstream microsoftStr;
		microsoftStr << std::fixed << std::setprecision(2) << microsoft;
		double airbus = ((rand() % 300) / 100.) + 98.5;
		std::ostringstream airbusStr;
		airbusStr << std::fixed << std::setprecision(2) << airbus;
		std::string mes = "Shares:\n\tApple - " + appleStr.str() + " (USD)\n"
			+ "\tMicrosoft - " + microsoftStr.str() + " (USD)\n"
			+ "\tAirbus - " + airbusStr.str() + " (USD)\n";
		SendMail(mes);
		Sleep(m_period);
	}
}

void SharesThread(void* Param) {
	Shares* This = (Shares*)Param;
	This->SendMailThread();
}