#include "CustomFunctions.h"

void SendString(std::string mes, SOCKET Connection) {
	int msg_size = mes.size();
	send(Connection, (char*)&msg_size, sizeof(int), NULL);
	send(Connection, mes.c_str(), msg_size, NULL);
}
