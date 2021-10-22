#ifndef ALGOTITHMS_H
#define ALGOTITHMS_H

#include <vector>
#include <string>


double BubbleSort(const std::vector<int>& inputVector);

double SelectionSort(const std::vector<int>& inputVector);

double ShellSort(const std::vector<int>& inputVector);

double QuickSort(const std::vector<int>& inputVector);
int partition (std::vector<int>& inputVector, int low, int high);
void quickSort(std::vector<int>& inputVector, int low, int high);

double MergeSort(const std::vector<int>& inputVector);
void merge(std::vector<int>& inputVector,const int left,const int mid,const int right);
void mergeSort(std::vector<int>& inputVector, const int begin,const int  end);

double CountingSort(const std::vector<int>& inputVector);

void WriteInFile(std::string path, std::vector<int> outputVecor);

#endif // ALGOTITHMS_H
