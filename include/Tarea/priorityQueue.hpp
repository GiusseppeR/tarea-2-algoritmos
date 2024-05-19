#ifndef PLAYCIRCLE_PRIORITYQUEUE_H
#define PLAYCIRCLE_PRIORITYQUEUE_H

#include<vector>

using namespace std;

class PriorityQueue {
public:
    virtual void heapify(vector<pair<int,int>> target);
    virtual pair<int,int> getMin() {return {0,0};}
    virtual pair<int,int> extractMin() {return {0,0};}
    virtual void decreaseKey(int node) {}
};
#endif //PLAYCIRCLE_PRIORITYQUEUE_H
