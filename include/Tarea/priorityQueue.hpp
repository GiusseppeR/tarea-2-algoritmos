#ifndef PLAYCIRCLE_PRIORITYQUEUE_H
#define PLAYCIRCLE_PRIORITYQUEUE_H

#include<vector>

using namespace std;

class PriorityQueue {
public:
    virtual void heapify(vector<pair<double, int> *> target){}
    virtual pair<double, int> *getMin() {return nullptr;}
    virtual pair<double, int> *extractMin() {return nullptr;}
    virtual void decreaseKey(pair<double, int> *pair, double distance) {}
    virtual bool isEmpty(){return true;}
};
#endif //PLAYCIRCLE_PRIORITYQUEUE_H
