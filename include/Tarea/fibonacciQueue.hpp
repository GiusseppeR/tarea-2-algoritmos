#ifndef TAREALOG_FIBONACCIQUEUE_HPP
#define TAREALOG_FIBONACCIQUEUE_HPP

#include <Tarea/priorityQueue.hpp>
#include <vector>

using namespace std;

class FibonacciQueue : public PriorityQueue{
private:
    pair<int,int> min;
    vector<BinomialTree> forest;
    //cualquier método extra, hacerlo privado
public:
    FibonacciQueue();
    void heapify(vector<pair<int,int>> target) override;
    pair<int,int> getMin() override;
    pair<int,int> extractMin() override;
    void decreaseKey(int node) override;
};

#endif
