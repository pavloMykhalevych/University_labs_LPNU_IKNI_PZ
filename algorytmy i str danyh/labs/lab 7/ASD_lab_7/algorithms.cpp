#include "algotithms.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>

void BubbleSort(const std::vector<int>& inputVector)
{
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

    }
    WriteInFile("outputBubbleSort",bubbleSortedVector);
}

void SelectionSort(const std::vector<int>& inputVector)
{
    std::vector<int> selectionSortedVector = inputVector;
    int min_idx;
        for (size_t i = 0; i < selectionSortedVector.size()-1; i++)
        {
            min_idx = i;
            for (size_t j = i+1; j < selectionSortedVector.size(); j++)
            if (selectionSortedVector[j] < selectionSortedVector[min_idx])
                min_idx = j;
            std::swap(selectionSortedVector[min_idx], selectionSortedVector[i]);
        }
        WriteInFile("outputSelectionSort",selectionSortedVector);
}

void ShellSort(const std::vector<int>& inputVector)
{
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
    WriteInFile("outputShellSort",shellSortedVector);
}

void QuickSort(const std::vector<int>& inputVector)
{
    std::vector<int> quickSortedVector = inputVector;
    quickSort(quickSortedVector,0,quickSortedVector.size()-1);
    WriteInFile("outputQuickSort",quickSortedVector);
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


void MergeSort(const std::vector<int>& inputVector)
{
    std::vector<int> mergeSortedVector = inputVector;
    mergeSort(mergeSortedVector,0,mergeSortedVector.size()-1);
    WriteInFile("outputMergeSort",mergeSortedVector);
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

void CountingSort(const std::vector<int>& inputVector)
{
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
    WriteInFile("outputCountingSort",countingSortedVector);
}

void WriteInFile(std::string path, const std::vector<int> outputVecor){
    std::ofstream file;
    file.open(path);
    std::string newstr;
    file << "/n/n/n" <<"Vector of " << outputVecor.size() << "elements" << "/n/n" << std::endl;
    int myIndex = 0;
    for(const auto& i : outputVecor){
        if(myIndex != 0 && myIndex % 8 == 0){
            file << std::endl;
            myIndex = -1;
        }
        file.width(15);
        file << i;
        file.width(0);
        file << "//";
        myIndex++;
    }
}
