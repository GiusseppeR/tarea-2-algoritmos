#ifndef TAREALOG_FIBONACCIQUEUE_HPP
#define TAREALOG_FIBONACCIQUEUE_HPP

#include <Tarea/priorityQueue.hpp>
#include <vector>

using namespace std;

class FibonacciQueue : public PriorityQueue{
private:
    //variables
public:
    FibonacciQueue();
    FibonacciQueue(vector<pair<int,int>> heapifyTarget);
    pair<int,int> getMin() override;
    pair<int,int> extractMin() override;
    void decreaseKey(int node) override;
};

#endif
