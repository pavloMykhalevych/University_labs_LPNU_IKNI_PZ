#include <iostream>
#include <vector>
#include <ctime>
#include <windows.h>
#include <sstream>




int main(int argc, const char* argv[])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int N;
    int M;
    std::stringstream str;

    srand(time(NULL));
    try {
        if (argc >= 2) {
            std::istringstream stdStream_1(argv[1]);
            std::istringstream stdStream_2(argv[2]);

            if (!(stdStream_1 >> N))
            {
                throw 1;
            }
            if (!(stdStream_2 >> M))
            {
                throw 1;
            }
        }
    }
    catch(int i){
        if (i == 1) {
            std::cout << std::endl <<"Invalid input";
            return 1;
        }
    }
    /*
    do {
        std::cout << "Enter the N :";
        std::cin >> N;
        if (N <= 1000) std::cout << "Error! Enter the right number." << std::endl;
        else break;
    } while (1);
    do {
        std::cout << std::endl << "Enter the M :";
        std::cin >> M;
        if (M <= 10000) std::cout << "Error! Enter the right number." << std::endl;
        else break;
    } while (1);
    */
    std::vector<std::vector<short>> matr(N, std::vector<short>(M,0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matr[i][j] = rand() % 100;
        }
    }
    std::vector<int> numberOfCount;
    for (int i = 0; i < M; i++) {
        int n = 0;
        for (int j = 1; j < N; j++) {
            if (matr[0][i] == matr[j][i]) {
                ++n;
            }
        }
        numberOfCount.push_back(n);
    }
    int k = 0;
    for (int i = 0; i < M; i++, k++)
    {
        if (k % 7 == 6) {
            SetConsoleTextAttribute(hConsole, 0x05);
        }
        else if (k % 7 == 5) {
            SetConsoleTextAttribute(hConsole, 0x03);
        }
        else if (k % 7 == 4) {
            SetConsoleTextAttribute(hConsole, 0x01);
        }
        else if (k % 7 == 3) {
            SetConsoleTextAttribute(hConsole, 0x02);
        }
        else if (k % 7 == 2) {
            SetConsoleTextAttribute(hConsole, 0x06);
        }
        else if (k % 7 == 1) {
            SetConsoleTextAttribute(hConsole, 0x0C);
        }
        else if (k % 7 == 0) {
            SetConsoleTextAttribute(hConsole, 0x04);
        }
        std::stringstream str_1;
        str << "The number of similar to first element in " << i << " column is "<< numberOfCount[i] << std::endl;
        str_1 << "The number of similar to first element in " << i << " column is "<< numberOfCount[i] << std::endl;
        std::string stringline = str_1.str();
        std::cout << stringline;

    }
    HANDLE file = CreateFile(L"C:\\LPNU\\os\\labs\\lab3\\OS_lab_3\\File.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file == INVALID_HANDLE_VALUE)
    {
        std::cout << "Can't open the file!" << std::endl;
        system("pause");
        return 2;
    }

    std::string buf = str.str();
    //HANDLE map = CreateFileMappingW(file, NULL, PAGE_READWRITE, NULL, buf.size(), NULL);
    //LPVOID pointer = MapViewOfFile(map, FILE_MAP_ALL_ACCESS, 0, 0, buf.size());
    //memcpy(pointer, buf.c_str(), buf.size());
    //UnmapViewOfFile(pointer);
    //CloseHandle(map);
    WriteFile(file, buf.c_str(), buf.size(), NULL, NULL);
    CloseHandle(file);
    SetConsoleTextAttribute(hConsole, 0xFFFF);
    system("pause");
    return 0;
}
