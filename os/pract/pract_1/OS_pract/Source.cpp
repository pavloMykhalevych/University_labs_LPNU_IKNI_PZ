#include <iostream>
#include <thread>
#include <windows.h>
#include <mutex>
int sum = 1000;
std::mutex mu;

void university() {
	for (auto i = 0; i < 100000; i++) {
		mu.lock();
		sum++;
		mu.unlock();
	}
	
}

void shop() {
	for (auto i = 0; i < 80000; i++) {
		mu.lock();
		sum--;
		mu.unlock();
	}
	
}

int main() {
	//int sum = 1000;
	/*std::thread t1(university);
	std::thread t2(shop);
	t1.join();
	t2.join();*/
	
	HANDLE myhandle{};
	HANDLE myhandle2{};
	DWORD mythreadid{};
	myhandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&university, 0, 0, &mythreadid);
	myhandle2 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&shop, 0, 0, &mythreadid);
	WaitForSingleObject(myhandle, INFINITE);
	WaitForSingleObject(myhandle2, INFINITE);
	CloseHandle(myhandle);
	CloseHandle(myhandle2);
	std::cout << sum;
	system("pause");
	return 0;
}