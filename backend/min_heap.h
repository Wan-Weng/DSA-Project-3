#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>
#include <algorithm>
#include "fooditems.h"
using namespace std;

class MinHeap { //Heap class for FoodItem objects that will be ordered by their health score
private:
    vector<FoodItem> heap; // vector stores heaps. smallest score will be at the top of heap

    int parent(int i) { return (i - 1) / 2; } //get parent node
    int left(int i) { return 2 * i + 1; } // get left index
    int right(int i) { return 2 * i + 2; } // right index 

    void HeapUp(int index) {
        for (int i = index; i > 0;) {
            int par = parent(i);
            if (heap[i].healthScore() < heap[par].healthScore()) {
                swap(heap[i], heap[par]); 
                i = par;
            } else {
                break; // Stop if the heap property is already satisfied
            }
        }
    }

    void HeapDown(int index) {
        int size = heap.size();
        int current = index;
    
        while (true) {
            int smallest = current;
            int l = left(current);
            int r = right(current);
    
            // Compare left 
            if (l < size && heap[l].healthScore() < heap[smallest].healthScore()) {
                smallest = l;
            }
    
            // Compare right
            if (r < size && heap[r].healthScore() < heap[smallest].healthScore()) {
                smallest = r;
            }
    
            // If the current node is already the smallest break
            if (smallest == current) break;
    
            // if not swap and continue
            swap(heap[current], heap[smallest]);
            current = smallest;
        }
    }

public:
    void push(const FoodItem& item) {
        heap.push_back(item);
        HeapUp(heap.size() - 1);
    }

    
    void pop() {
        // Check if the heap is empty before popping
        if (heap.empty()) {
            // if heap empty just return
            return;
        }
        // Replace the top element with the last element
        heap[0] = heap.back();
        // Remove the last element
        heap.pop_back();
        if (!heap.empty()) {
            HeapDown(0);
        }
    }

    FoodItem top() const {
        // Return the top element if the heap is not empty
        if (!heap.empty()) {
            return heap[0];
        }
        return FoodItem();
    }

    int size() const {
        return heap.size();
    }


    vector<FoodItem> getSortedDescending() {
        // Create a copy of the current heap
        vector<FoodItem> dup;
        for (const auto& item : heap) {
            dup.push_back(item);
        }
    
        // Sort the copy in descending order
        sort(dup.begin(), dup.end(), [](const FoodItem& a, const FoodItem& b) {
            // Items with higher healthScore should come first
            if (a.healthScore() > b.healthScore()) {
                return true;
            } else {
                return false;
            }
        });
    
        return dup;
    }
};

#endif
