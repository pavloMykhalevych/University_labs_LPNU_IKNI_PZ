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

/*#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>
int sum = 1000;

std::mutex mut;
HANDLE mutex;
HANDLE semaphore;
void univer()
{
    DWORD dwCode;
  for (int i = 0; i < 1000000; i++)
  {
    //WaitForSingleObject(mutex, INFINITE);
    //mut.lock();
    dwCode = WaitForSingleObject(semaphore, INFINITE);
    Sleep(1);
    ++sum;
    ReleaseSemaphore(semaphore, 1, nullptr);
    //ReleaseMutex(mutex);
    //mut.unlock();
  }
}void shop()
{
  for (int i = 0; i < 800000; ++i)
  {
    WaitForSingleObject(semaphore, INFINITE);
    Sleep(1);
    //WaitForSingleObject(mutex, INFINITE);
    //mut.lock();
    --sum;
    ReleaseSemaphore(semaphore, 1, nullptr);
    //ReleaseMutex(mutex);
    //mut.unlock();
  }
}

void Bank() {

  //ReleaseMutex(mutex);
  ReleaseSemaphore(semaphore, 1, nullptr);
  Sleep(1);
}
int main()
{

  mutex = CreateMutex(nullptr, FALSE, nullptr);
  semaphore = CreateSemaphore(0, 1, 1, nullptr);
  std::thread th1(&univer);
  std::thread th2(&shop);
  std::thread th3(&Bank);
  th1.join();
  th2.join();
  th3.join();
  std::cout << sum;
  CloseHandle(mutex);
  CloseHandle(semaphore);
  return 0;
}*/