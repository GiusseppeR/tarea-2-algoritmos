#include <Tarea/fibonacciQueue.hpp>

FibonacciQueue::FibonacciQueue() {}


void FibonacciQueue::heapify(vector<pair<int, int>> target) {}

pair<int, int> FibonacciQueue::getMin() {
    if(min == nullptr) {
        return{INFINITY, -1};
    }
    return{min->distance, min->key};
}

pair<int, int> FibonacciQueue::extractMin() {

}


void FibonacciQueue::decreaseKey(int node) {}