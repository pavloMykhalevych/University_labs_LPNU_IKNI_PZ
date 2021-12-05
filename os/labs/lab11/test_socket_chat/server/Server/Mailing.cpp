#include "Mailing.h"

Mailing::Mailing(int time) : m_period(time) {

}

void Mailing::AddSubscribed(SOCKET newClient) {
	m_subscribed.insert(newClient);
}

void Mailing::SendMail(std::string mes) {
	for (const auto& connection : m_subscribed) {
		SendString(mes, connection);
	}
}

bool Mailing::Find(SOCKET connection) {
	if (m_subscribed.find(connection) != m_subscribed.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::string Mailing::Delete(SOCKET connection) {
	if (Find(connection)) {
		m_subscribed.erase(connection);
		return "You have been successfully unsubscribed. Sorry for annoying you ;(";
	}
	else {
		return "You haven't been subscribed on our service.";
	}
}