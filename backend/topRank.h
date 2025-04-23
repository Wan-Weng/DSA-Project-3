#ifndef TOPK_H
#define TOPK_H

#include <vector>
#include <algorithm>
#include <chrono>
#include "filters.h"
#include "min_heap.h"
#include "fooditems.h"
using namespace std;

vector<FoodItem> getTopK_Heap(const vector<FoodItem>& filtered, int k) {
    MinHeap heap;
    for (const auto& item : filtered) {
        heap.push(item);
        if (heap.size() > k) {
            heap.pop(); // remove lowest score
        }
    }
    return heap.getSortedDescending();
}

vector<FoodItem> getTopK_Sort(vector<FoodItem> filtered, int k) {
    sort(filtered.begin(), filtered.end(), [](const FoodItem& a, const FoodItem& b) {
        return a.healthScore() > b.healthScore();
    });

    if (filtered.size() > k) {
        filtered.resize(k);
    }
    return filtered;
}

struct TopKResult {
    int k;
    long long heap_time_ms;
    long long sort_time_ms;
    vector<FoodItem> heap_results;
    vector<FoodItem> sort_results;
};

TopKResult runTopKSearch(
    const vector<FoodItem>& fullData,
    float minProtein,
    float maxSugar,
    float minFiber,
    int k
) {
    TopKResult result;
    result.k = k;

    vector<FoodItem> filtered = filterData(
        fullData,
        minProtein,
        maxSugar,
        minFiber
    );

    auto startHeap = chrono::high_resolution_clock::now();
    result.heap_results = getTopK_Heap(filtered, k);
    auto endHeap = chrono::high_resolution_clock::now();
    result.heap_time_ms = chrono::duration_cast<chrono::milliseconds>(endHeap - startHeap).count();

    auto startSort = chrono::high_resolution_clock::now();
    result.sort_results = getTopK_Sort(filtered, k);
    auto endSort = chrono::high_resolution_clock::now();
    result.sort_time_ms = chrono::duration_cast<chrono::milliseconds>(endSort - startSort).count();

    return result;
}

#endif
