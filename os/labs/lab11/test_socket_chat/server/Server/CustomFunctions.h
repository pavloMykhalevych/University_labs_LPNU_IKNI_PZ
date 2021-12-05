#pragma once

#include <winsock2.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

void SendString(std::string mes, SOCKET Connection);
