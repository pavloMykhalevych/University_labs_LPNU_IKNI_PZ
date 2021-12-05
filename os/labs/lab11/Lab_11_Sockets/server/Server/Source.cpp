#pragma comment(lib, "ws2_32.lib")

#include "Includes.h"

#include "Weather.h"
#include "Currency.h"
#include "Shares.h"

#pragma warning(disable: 4996)

Weather weatherMail(60000);
Currency currencyMail(10000);
Shares sharesMail(25000);
std::vector<SOCKET> Connections;
std::unordered_set<SOCKET> Subscribed;
int Counter = 0;

void ClientHandler(int index);

int main(int argc, char* argv[]) {

	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected!\n";
			SendString("Welcome to the mailing service)\nIf you want to subscribe on some services, choose onr from this:\n"
				"1) Weather mailing;\n2)Currency mailing;\n3)Shares mailing;\n"
				"Note: If you will need to unsubscribe from one of services write: \"Delete\" and number of service.", newConnection);
			Connections.push_back(newConnection);
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}


	system("pause");
	return 0;
}

void ClientHandler(int index) {
	int msg_size;
	while (true) {
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		if (!strcmp(msg, "1")) {
			if (!weatherMail.Find(Connections[index])) {
				weatherMail.AddSubscribed(Connections[index]);
				SendString("You have been subscribed on weather mailing. Thanks!", Connections[index]);
			}
			else {
				SendString("You have been already subscribed on weather mailing. There is no point to do it again.", Connections[index]);
			}
		}
		else if(!strcmp(msg, "2")) {
			if (!currencyMail.Find(Connections[index])) {
				currencyMail.AddSubscribed(Connections[index]);
				SendString("You have been subscribed on currency mailing. Thanks!", Connections[index]);
			}
			else {
				SendString("You have been already subscribed on currency mailing. There is no point to do it again.", Connections[index]);
			}
		}
		else if (!strcmp(msg, "3")) {
			if (!sharesMail.Find(Connections[index])) {
				sharesMail.AddSubscribed(Connections[index]);
				SendString("You have been subscribed on shares mailing. Thanks!", Connections[index]);
			}
			else {
				SendString("You have been already subscribed on shares mailing. There is no point to do it again.", Connections[index]);
			}
		}
		else if (!strcmp(msg, "Delete 1")) {
			SendString(weatherMail.Delete(Connections[index]), Connections[index]);
		}
		else if (!strcmp(msg, "Delete 2")) {
			SendString(currencyMail.Delete(Connections[index]), Connections[index]);
		}
		else if (!strcmp(msg, "Delete 3")) {
			SendString(sharesMail.Delete(Connections[index]), Connections[index]);
		}
		delete[] msg;
	}
}
