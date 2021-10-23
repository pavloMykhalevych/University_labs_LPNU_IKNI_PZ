#include "algotithms.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
#include <chrono>

double BubbleSort(const std::vector<int>& inputVector)
{
    auto begin = std::chrono::high_resolution_clock::now();
    std::cout << "Bubble sort for " << inputVector.size() << " elements starts."<< std::endl;
    std::vector<int> bubbleSortedVector = inputVector;
    for (size_t i = 0; i < bubbleSortedVector.size()-1; i++){
        bool F = false;
        for (size_t j = 0; j < bubbleSortedVector.size()-i-1; j++) {
            if (bubbleSortedVector[j] > bubbleSortedVector[j+1]) {
                std::swap(bubbleSortedVector[j], bubbleSortedVector[j+1]);
                F = true;
            }
        }
        if(F == false) break;
        auto end_loop = std::chrono::high_resolution_clock::now();
        auto elapsed_loop = std::chrono::duration_cast<std::chrono::microseconds>(end_loop - begin);
        if(elapsed_loop.count() * 1e-6 > 120){
            break;
        }

    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    //WriteInFile("outputBubbleSort",bubbleSortedVector);
    return elapsed.count() * 1e-6;
}

double SelectionSort(const std::vector<int>& inputVector)
{
    auto begin = std::chrono::high_resolution_clock::now();
    std::cout << "Selection sort for " << inputVector.size() << " elements starts."<< std::endl;
    std::vector<int> selectionSortedVector = inputVector;
    int min_idx;
        for (size_t i = 0; i < selectionSortedVector.size()-1; i++)
        {
            min_idx = i;
            for (size_t j = i+1; j < selectionSortedVector.size(); j++)
            if (selectionSortedVector[j] < selectionSortedVector[min_idx])
                min_idx = j;
            std::swap(selectionSortedVector[min_idx], selectionSortedVector[i]);
            auto end_loop = std::chrono::high_resolution_clock::now();
            auto elapsed_loop = std::chrono::duration_cast<std::chrono::microseconds>(end_loop - begin);
            if(elapsed_loop.count() * 1e-6 > 120){
                break;
            }
        }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    //WriteInFile("outputSelectionSort",selectionSortedVector);
    return elapsed.count() * 1e-6;
}

double ShellSort(const std::vector<int>& inputVector)
{
    auto begin = std::chrono::high_resolution_clock::now();
    std::cout << "Shell sort for " << inputVector.size() << " elements starts."<< std::endl;

    std::vector<int> shellSortedVector = inputVector;

    int d = (shellSortedVector.size()-1 - 0) / 2;

    while(d >= 1){
        for (size_t i = 0 + d; i < shellSortedVector.size()-1; i++) {
            for (int j = i; j >= 0; j -= d ) {
                int min_Index = j;
                for (int k = j-d; k >= 0; k -= d ) {
                    if(shellSortedVector[k]<shellSortedVector[min_Index]){
                        min_Index = k;
                    }
                    auto end_loop = std::chrono::high_resolution_clock::now();
                    auto elapsed_loop = std::chrono::duration_cast<std::chrono::milliseconds>(end_loop - begin);
                    if((elapsed_loop.count() * 1e-3) > std::chrono::seconds{10}.count()){
                        return elapsed_loop.count() * 1e-3;
                    }
                }
                if(min_Index != j){
                    int tmp = shellSortedVector[min_Index];
                    shellSortedVector[min_Index] = shellSortedVector[j];
                    shellSortedVector[j] = tmp;
                }
            }

        }

        d /= 2;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    //WriteInFile("outputShellSort",shellSortedVector);
    return elapsed.count() * 1e-6;
}

double QuickSort(const std::vector<int>& inputVector)
{
    auto begin = std::chrono::high_resolution_clock::now();
    std::cout << "Quick sort for " << inputVector.size() << " elements starts."<< std::endl;
    std::vector<int> quickSortedVector = inputVector;
    quickSort(quickSortedVector,0,quickSortedVector.size()-1);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    //WriteInFile("outputQuickSort",quickSortedVector);
    return elapsed.count() * 1e-6;
}

int partition (std::vector<int>& inputVector, int low, int high)
{
    int pivot = inputVector[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (inputVector[j] < pivot)
        {
            i++;
            int t = inputVector[j];
            inputVector[j] = inputVector[i];
            inputVector[i] = t;
        }
    }

    int t = inputVector[i + 1];
    inputVector[i + 1] = inputVector[high];
    inputVector[high] = t;

    return (i + 1);
}


void quickSort(std::vector<int>& inputVector, int low, int high)
{
    if (low < high)
    {

        int pi = partition(inputVector, low, high);


        quickSort(inputVector, low, pi - 1);
        quickSort(inputVector, pi + 1, high);
    }
}


double MergeSort(const std::vector<int>& inputVector)
{
    auto begin = std::chrono::high_resolution_clock::now();
    std::cout << "Merge sort for " << inputVector.size() << " elements starts."<< std::endl;
    std::vector<int> mergeSortedVector = inputVector;
    mergeSort(mergeSortedVector,0,mergeSortedVector.size()-1);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    //WriteInFile("outputMergeSort",mergeSortedVector);
    return elapsed.count() * 1e-6;
}

void merge(std::vector<int>& inputVector,const int left,const int mid,const int right)
{
    const int  subArrayOneCount = mid - left + 1;
    const int subArrayTwoCount = right - mid;


    int *leftArray = new int[subArrayOneCount],
         *rightArray = new int[subArrayTwoCount];


    for (int i = 0; i < subArrayOneCount; i++)
        leftArray[i] = inputVector[left + i];
    for (int j = 0; j < subArrayTwoCount; j++)
        rightArray[j] = inputVector[mid + 1 + j];

    int indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    // Merge
    while (indexOfSubArrayOne < subArrayOneCount && indexOfSubArrayTwo < subArrayTwoCount) {
        if (leftArray[indexOfSubArrayOne] >= rightArray[indexOfSubArrayTwo]) {
            inputVector[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            inputVector[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOneCount) {
        inputVector[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwoCount) {
        inputVector[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }


    delete [] leftArray;
    delete [] rightArray;
}


void mergeSort(std::vector<int>& inputVector, const int begin,const int  end)
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(inputVector, begin, mid);
    mergeSort(inputVector, mid + 1, end);
    merge(inputVector, begin, mid, end);
}

double CountingSort(const std::vector<int>& inputVector)
{
    auto begin = std::chrono::high_resolution_clock::now();
    std::cout << "Counting sort for " << inputVector.size() << " elements starts."<< std::endl;
    std::vector<int> countingSortedVector = inputVector;
    std::map<int,int> keys_values;
    for(size_t i = 0; i < countingSortedVector.size(); i++)
    {
        keys_values[countingSortedVector[i]]++;
    }

    int ind = 0;
    for(auto it : keys_values){
        int val = it.first;
        int freq = it.second;
        for (int j = 0;j < freq ;j++ ) {
            countingSortedVector[ind] = val;
            ind++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    //WriteInFile("outputCountingSort",countingSortedVector);
    return elapsed.count() * 1e-6;
}

void WriteInFile(std::string path, const std::vector<int> outputVecor){
    std::ofstream file;
    if(outputVecor.size() == 1024){
        file.open(path);
    }else{
        file.open(path, std::ios::app);
    }
    std::string newstr;
    file << "\n\n\n" <<"Vector of " << outputVecor.size() << "elements" << "\n\n" << std::endl;
    int myIndex = 0;
    for(const auto& i : outputVecor){
        if(myIndex != 0 && myIndex % 5 == 0){
            file << std::endl;
            myIndex = 0;
        }
        file.width(15);
        file << i;
        file.width(0);
        file << "//";
        myIndex++;
    }
}
