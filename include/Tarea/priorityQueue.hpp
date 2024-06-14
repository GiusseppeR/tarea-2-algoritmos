#ifndef PLAYCIRCLE_PRIORITYQUEUE_H
#define PLAYCIRCLE_PRIORITYQUEUE_H

#include<vector>

using namespace std;

class PriorityQueue {
public:
    virtual void heapify(vector<pair<double, int>> target){}
    virtual pair<double, int> getMin() {return {0,0};}
    virtual pair<double, int> extractMin() {return {0,0};}
    virtual void decreaseKey(int pair, double distance) {}
    virtual bool isEmpty(){return true;}
};
#endif //PLAYCIRCLE_PRIORITYQUEUE_H
