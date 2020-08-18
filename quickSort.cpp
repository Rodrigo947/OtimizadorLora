#include <vector>
#include "json.hpp" //leitor de json
#include "QuickSort.h"

using namespace std;
using json = nlohmann::json;

void swap(json *a, json *b)
{
    json t = *a;
    *a = *b;
    *b = t;
}

int partition(vector<json> *arr, int low, int high)
{
    json pivot = arr->at(high);
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr->at(j)["quant"] < pivot["quant"])
        {
            i++;
            swap(&arr->at(i), &arr->at(j));
        }
    }
    swap(&arr->at(i + 1), &arr->at(high));
    return (i + 1);
}

void quickSort(vector<json> *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}