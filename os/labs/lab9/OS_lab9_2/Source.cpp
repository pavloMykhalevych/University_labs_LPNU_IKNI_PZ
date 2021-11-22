
#include <iostream>
#include <windows.h>

HINSTANCE h;

int main() {

	void (*DllFunc)();

	h = LoadLibrary(L"OS_dll_1.dll");

	if (!h) {
		std::cout << "Can't find dll.";
		return 1;
	}

	DllFunc = (void(*)())GetProcAddress(h, "DynamicLibFunc");

	if (!DllFunc) {
		return 2;
	}


	std::cout << "Dynamic lib:" << std::endl;
	DllFunc();
	FreeLibrary(h);

	return 0;
}