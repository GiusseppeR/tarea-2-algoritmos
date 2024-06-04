#include <Tarea/fibonacciQueue.hpp>

FibonacciQueue::FibonacciQueue(): min(nullptr), c(0) {}

void FibonacciQueue:: insert(int node, double dist) {
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

void FibonacciQueue::adjust() {
    int maxDegree= log2(c) + 1;
    vector<FibonacciNode*> nodeList(maxDegree, nullptr);
    vector<FibonacciNode*> roots;
    FibonacciNode* currMin=min;
    if(currMin!=nullptr) {
        do {
            roots.push_back(currMin);
            currMin=currMin->r;
        } while(currMin!=min);
    }
    for(FibonacciNode* x: roots) {
        FibonacciNode* currMin=x;
        int i= currMin->degree;
        while(nodeList[i] != nullptr) {
            FibonacciNode * y= nodeList[i];
            if(currMin->distance > y ->distance) {
                swap(currMin, y);
            }
            link(y, currMin);
            nodeList[i]= nullptr;
            i++;
        }
        nodeList[i]=currMin;
    }
    min=nullptr;
    for(FibonacciNode* y: nodeList) {
        if(y != nullptr) {
            if(min==nullptr) {
                min=y;
                min->l=min;
                min->r=min;
            }
            else {
                y->l=min;
                y->r= min->r;
                min->r->l =y;
                min -> r= y;
                if(y -> distance < min->distance) {
                    min=y;
                }

            }
        }
    }

}
void FibonacciQueue::link(FibonacciNode* y, FibonacciNode* x) {
    y->l->r=y->r;
    y->r->l=y->l;
    y->parent=x;
    if(x->child==nullptr) {
        x->child=y;
        y->r=y;
        y->l=y;
    }
    else {
        y->l=x->child;
        y->r=x->child->r;
        x->child->r->l=y;
        x->child->r=y;
    }
    x->degree++;
    y->marked= false;
}

void FibonacciQueue::heapify(vector<pair<double, int>*> target) { //vector de punteros de pares (dist, nodo)
    for(auto& x : target) {
        insert(x->second,x->first);
    }
}

pair<double, int>* FibonacciQueue::getMin() {
    if(min == nullptr) {
        return nullptr;
    }
    return new pair(min->distance, min->key);
}

pair<double, int>* FibonacciQueue::extractMin() {
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
        currMin ->l->r=currMin->r;
        currMin->r->l= currMin->l;
        if(currMin==(currMin->r)) {
            min=nullptr;
        }
        else {
            min=currMin->r;
            adjust();
        }
        c--;
    }
    int keyNode= currMin-> key;
    double distanceNode=currMin->distance;
    elements.erase(keyNode);
    delete currMin;
    return new pair(distanceNode, keyNode);
}



// x hijo e y padre cortaremos x de y
void FibonacciQueue::cut(FibonacciNode* x, FibonacciNode* y) {
    if(x -> r == x) { //caso en q x es el unico hijo
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

void FibonacciQueue::propagatingCut(FibonacciNode* y) {
    FibonacciNode* x = y->parent;
    if(x!=nullptr) {
        if(y->marked== false) {
            y->marked=true;
        }
        else {
            cut(y, x);
            propagatingCut(x);
        }
    }
}
void FibonacciQueue::decreaseKey(pair<double, int>* p, double newDist) {
    int key= p->second;
    FibonacciNode* x= elements[key];
    x->distance= newDist;
    FibonacciNode* y=x->parent;
    if(y != nullptr && x-> distance < y-> distance ) {
        cut(x,y);
        propagatingCut(y);
    }
    if(x->distance < min->distance) {
        min=x;
    }

}

