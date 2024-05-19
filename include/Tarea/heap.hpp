#ifndef TAREALOG_HEAP_HPP
#define TAREALOG_HEAP_HPP

#include <Tarea/priorityQueue.hpp>
#include <vector>

using namespace std;

class Heap : public PriorityQueue{
private:
    pair<int,int> min;
    vector<pair<int,int>> heap;
    //cualquier método extra, hacerlo privado
public:
    Heap();
    void heapify(vector<pair<int,int>> target) override;
    pair<int,int> getMin() override;
    pair<int,int> extractMin() override;
    void decreaseKey(int node) override;
};

#endif //TAREALOG_HEAP_HPP
