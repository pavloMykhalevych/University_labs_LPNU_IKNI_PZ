#ifndef ALGOTITHMS_H
#define ALGOTITHMS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

void BubbleSort(const std::vector<int>& inputVector);

void SelectionSort(const std::vector<int>& inputVector);

void ShellSort(const std::vector<int>& inputVector);

void QuickSort(const std::vector<int>& inputVector);
int partition (std::vector<int>& inputVector, int low, int high);
void quickSort(std::vector<int>& inputVector, int low, int high);

void MergeSort(const std::vector<int>& inputVector);
void merge(std::vector<int>& inputVector,const int left,const int mid,const int right);
void mergeSort(std::vector<int>& inputVector, const int begin,const int  end);

void CountingSort(const std::vector<int>& inputVector);

#endif // ALGOTITHMS_H
