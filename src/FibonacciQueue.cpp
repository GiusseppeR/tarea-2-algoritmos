#include <Tarea/fibonacciQueue.hpp>

FibonacciQueue::FibonacciQueue(): min(nullptr), c(0) {}

void FibonacciQueue:: insert(int node, int dist) {
    FibonacciNode* insertNode=  new FibonacciNode(node, dist);
    elements[node] = insertNode;
    if(min==nullptr) {//caso vacio
        min=insertNode;
    }
    else {
        insertNode->l=min;
        insertNode->r=min->r;
        min->r->l=insertNode;
        min -> r=insertNode;
        if(min->distance>insertNode->distance) {
            //actualizamos min si es necesario
            min=insertNode;
        }
    }
    c++;
}

void FibonacciQueue::heapify(vector<pair<int, int>> target) { //vector de punteros de pares (dist, nodo)
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
    FibonacciNode* currMin = min;
    if(currMin != nullptr) {
        if(currMin->child != nullptr) {
            FibonacciNode* minChild= currMin->child;
            do {
                FibonacciNode* next = minChild -> r;
                minChild->l->r=minChild->r;
                minChild->r->l = minChild-> l;

                minChild->l=currMin;
                minChild->r= currMin->r;

                currMin->r->l=minChild;
                currMin->r=minChild;
                minChild->parent=nullptr;
                minChild=next;
            }while(minChild != currMin->child);
        }


    }
}

void FibonacciQueue::decreaseKey(int node) {

}

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