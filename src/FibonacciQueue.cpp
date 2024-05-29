#include <Tarea/fibonacciQueue.hpp>

FibonacciQueue::FibonacciQueue(): min(nullptr), c(0) {}

void FibonacciQueue:: insert(int node, int dist) {

}

void FibonacciQueue::heapify(vector<pair<int, int>> target) {
    for(const auto& [node, dist] : target) {
        insert(node,dist);
    }
}

pair<int, int> FibonacciQueue::getMin() {
    if(min == nullptr) {
        return{INFINITY, -1};
    }
    return{min->distance, min->key};
}

pair<int, int> FibonacciQueue::extractMin() {

}


void FibonacciQueue::decreaseKey(int node) {}

// x hijo e y padre cortaremos x de y
void FibonacciQueue::cut(FibonacciNode* x, FibonacciNode* y) {
    if(x -> r == x && x -> l == x) { //caso en q x es el unico hijo
        y-> child = nullptr;

    }
    else {
        x->r->l = x ->l;
        x->l->r=x->r;
        if(y->child==x) {
            y->child = x->r;
        }
    }
    y-> degree--;
    x->l= min;
    x->r= min->r;
    min->r->l=x;
    x->parent= nullptr;
    x->marked= false;
}