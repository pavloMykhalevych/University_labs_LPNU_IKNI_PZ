#include "StaticLib1.h"
#include "Functions.h"
#include <iostream>

int main() {
	std::cout << "Static lib:" << std::endl;
	StaticLibFunc();

	std::cout << "Dynamic lib:" << std::endl;
	DynamicLibFunc();

	return 0;
}