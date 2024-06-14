#ifndef TAREALOG_HEAP_HPP
#define TAREALOG_HEAP_HPP
#include <iostream>
#include <Tarea/priorityQueue.hpp>
#include <vector>
#include <utility>
#include <random>
using namespace std;

/**
 * @class Heap
 * @brief Clase que implementa una cola de prioridad utilizando la estructura heap
 */
class Heap : public PriorityQueue{
private:
    size_t heapSize = 0;
    vector<int> nodeIndex;
    vector<pair<double,int>> heapData;

    static int parent(int i);
    static int left(int i);
    static int right(int i);
    void minHeapify(int i);
    int find(int node);
    double metric(int i);

public:
    Heap();
    pair<double,int> getMin() override;
    pair<double,int> extractMin() override;
    void decreaseKey(int node, double k) override;
    void heapify(vector<pair<double, int>> target) override;
    bool isEmpty() override;
};

#endif //TAREALOG_HEAP_HPP
