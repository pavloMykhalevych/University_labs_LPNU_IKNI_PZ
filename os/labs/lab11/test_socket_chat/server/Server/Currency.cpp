#include "Currency.h"

Currency::Currency(int time) : Mailing(time) {
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CurrencyThread, (void*)this, NULL, NULL);
}

void Currency::SendMailThread() {
	while (true) {
		srand(time(NULL));
		double euro = ((rand() % 150) / 100.) + 30.6;
		std::ostringstream euroStr;
		euroStr << std::fixed << std::setprecision(2) << euro;
		double dollar = ((rand() % 150) / 100.) + 27.2;
		std::ostringstream dollarStr;
		dollarStr << std::fixed << std::setprecision(2) << dollar;
		double chf = ((rand() % 150) / 100.) + 29.5;
		std::ostringstream chfStr;
		chfStr << std::fixed << std::setprecision(2) << chf;
		std::string mes = "Currency:\n\t1 (EUR) - " + euroStr.str() + " (UAH)\n"
			+ "\t1 (USD) - " + dollarStr.str() + " (UAH)\n"
			+ "\t1 (CHF) - " + chfStr.str() + " (UAH)\n";
		SendMail(mes);
		Sleep(m_period);
	}
}

void CurrencyThread(void* Param) {
	Currency* This = (Currency*)Param;
	This->SendMailThread();
}