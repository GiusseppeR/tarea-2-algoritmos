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
    void heapify(vector<pair<double, int> *> target) override;
    pair<double, int> * getMin() override;
    pair<double, int> * extractMin() override;
    void decreaseKey(pair<double, int> *pair, double distance) override;
};

#endif //TAREALOG_HEAP_HPP
