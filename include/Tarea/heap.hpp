#ifndef TAREALOG_HEAP_HPP
#define TAREALOG_HEAP_HPP

#include <Tarea/priorityQueue.hpp>
#include <vector>

using namespace std;

class Heap : public PriorityQueue{
private:
    //variables
public:
    Heap();
    Heap(vector<pair<int,int>> heapifyTarget);
    pair<int,int> getMin() override;
    pair<int,int> extractMin() override;
    void decreaseKey(int node) override;
};

#endif //TAREALOG_HEAP_HPP
