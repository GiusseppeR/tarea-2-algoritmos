#ifndef FIBONACCI_QUEUE_HPP
#define FIBONACCI_QUEUE_HPP

#include "node.hpp"
#include "priorityQueue.hpp"
#include <unordered_map>
#include <vector>
#include <list>


class FibonacciQueue : public PriorityQueue {
private:
    Node* min;
    int n;
    std::unordered_map<int, Node*> nodes;  // Mapa de vértice a puntero de nodo
    void consolidate();
    void link(Node* y, Node* x);
    void cut(Node* x, Node* y);
    void cascadingCut(Node* y);

public:
    FibonacciQueue() : min(nullptr), n(0) {}
    void heapify(vector<pair<double, int>*> target) override;
    pair<double, int>* getMin() override;
    pair<double, int>* extractMin() override;
    void decreaseKey(pair<double, int>* p, double distance) override;
    bool isEmpty() override {
        return n == 0;
    }
};

#endif // FIBONACCI_QUEUE_HPP

