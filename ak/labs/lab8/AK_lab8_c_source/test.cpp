#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <ctype.h>
#include <vector>

//
//void RemoveSpaces(std::string& myString) {
//    for (size_t i = 1; i < myString.size(); ++i) {
//        if (myString[i - 1] == ' ' && (myString[i] == ' ' || myString[i] == '\0')) {
//            myString.erase(myString.begin() + (i - 1));
//            myString.shrink_to_fit();
//            i--;
//        }
//    }
//}
//
//int main() {
//    std::string str = "Remove     additional    spaces   ";
//    RemoveSpaces(str);
//    std::cout << str << "\nEnd.";
//	return 0;
//}
int partition(std::string& arr, int low, int high)
{
    char pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] < pivot)
        {
            i++;
            char t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
        }
    }

    char t = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t;
    return (i + 1);
}


void quickSort(std::string& arr, int low, int high)
{
    if (low < high)
    {

        int pi = partition(arr, low, high);


        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    std::string InputString = "Mykhalevycj  UUWUDaa";
    std::string stringToSort;
    for (size_t i = 0; i < InputString.length(); i++)
    {
        if (std::islower(InputString[i])) {
            stringToSort.push_back(InputString[i]);
        }
    }
    std::cout << stringToSort<<std::endl;
    quickSort(stringToSort,0, stringToSort.length()-1);
    std::cout << stringToSort;
}