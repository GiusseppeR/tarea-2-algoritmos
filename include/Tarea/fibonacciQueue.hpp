#ifndef TAREALOG_FIBONACCIQUEUE_HPP
#define TAREALOG_FIBONACCIQUEUE_HPP

#include <Tarea/priorityQueue.hpp>
#include <Tarea/binomialTree.hpp>
#include <vector>

using namespace std;

class FibonacciQueue : public PriorityQueue{
private:
    pair<int,int> min;
    vector<BinomialTree> forest;
    //cualquier método extra, hacerlo privado
public:
    FibonacciQueue();
    void heapify(vector<pair<double, int> *> target) override;
    pair<double, int> * getMin() override;
    pair<double, int> * extractMin() override;
    void decreaseKey(pair<double, int> *pair, double distance) override;
};

#endif
