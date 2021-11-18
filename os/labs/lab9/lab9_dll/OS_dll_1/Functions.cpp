#include "pch.h"

#include "Functions.h"

#include <Windows.h>
#include <vector>
#include <iostream>
#include <mutex>

int sum = 0;
std::vector<int> array(10000, 0);
std::mutex mu;

std::vector<HANDLE> myhandle(4, 0);
std::vector<DWORD> mythreadid(4, 0);

void ArraySum(int* param) {
    mu.lock();
    for (int i = param[0]; i < param[1]; i++) {
        if (i == 0) {
            array[i] = 2;
            sum += array[i];
            continue;
        }
        array[i] = array[i - 1] * i + exp(i);
        sum += array[i];
        //sum += 1;
        //std::cout << myindex++ << " / " << std::endl;
    }
    std::cout << "In current thread (" << GetCurrentThreadId() << "): sum =" << sum << std::endl;
    mu.unlock();
}

void DynamicLibFunc() {
    for (int i = 0; i < 4; i++) {
        int* param = new int[2];
        param[0] = (i) * (10000 / 4);
        param[1] = (i + 1) * (10000 / 4);
        myhandle[i] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ArraySum, param, 0, &mythreadid[i]);
    }
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(myhandle[i], INFINITE);
        CloseHandle(myhandle[i]);
    }
}