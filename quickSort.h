#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <iostream>
#include <vector>
#include "json.hpp" //leitor de json

using namespace std;
using json = nlohmann::json;

void quickSort(vector<json> *arr, int low, int high);
void quickSortDesc(vector<json> *arr, int low, int high);

#endif