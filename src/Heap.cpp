#include <Tarea/heap.hpp>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <numeric>
Heap::Heap() = default;

int Heap::parent(int i) {
    return (i+1)/2 - 1;
}
int Heap::left(int i) {
    return (i+1)*2 -1;
}
int Heap::right(int i) {
    return (i+1)*2;
}
int Heap::find(pair<double,int>* node) {
    if (nodeIndex[node->second] == -1) {
        throw std::runtime_error("Node dosen't exit in array");
    }
    return nodeIndex[node->second];
}

bool Heap::isEmpty() {
    return heapSize == 0;
}


double Heap::metric(int i) {
    return heapData.at(i)->first;
}
void Heap::minHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest;
    if (l < heapSize && metric(l)<metric(i)) {
        smallest = l;
    } else {
        smallest = i;
    }
    if (r<heapSize && metric(r)<metric(smallest)) {
        smallest = r;
    }
    if (smallest != i) {
        // usando nodeIndex
        int index = heapData[i]->second;
        int sIndex = heapData[smallest]->second;
        nodeIndex[index] = smallest;
        nodeIndex[sIndex] = i;
        //
        swap(heapData[i],heapData[smallest]);
        minHeapify(smallest);
    }
}
void Heap::heapify(vector<pair<double, int> *> target) {
    heapData = target;
    heapSize = target.size();
    nodeIndex.resize(heapSize);
    iota(nodeIndex.begin(), nodeIndex.end(), 0);
    int i = (static_cast<int>(heapSize)/2) - 1;
    while (i>=0) {
        minHeapify(i);
        i--;
    }
}
pair<double, int>* Heap::getMin() {
    return heapData[0];
}

pair<double, int>* Heap::extractMin() {
    pair<double,int>* min = getMin();
    if (heapSize>1) heapData[0] = heapData[heapSize-1];
    //usando nodeIndex
    nodeIndex[0] = heapData[0]->second;
    nodeIndex.pop_back();
    //
    heapData.pop_back();
    heapSize-=1;
    minHeapify(0);
    return min;
}

void Heap::decreaseKey(pair<double,int>* node, double k) {
    int i = find(node);
    if (heapData[i]->first < k) {
        return ;
    }
    heapData[i]->first = k;
    while (i>0 && heapData[parent(i)]->first > heapData[i]->first) {
        // usando nodeIndex
        int index = heapData[i]->second;
        int pIndex = heapData[parent(i)]->second;
        nodeIndex[index] = parent(i);
        nodeIndex[pIndex] = i;
        //
        swap(heapData[i],heapData[parent(i)]);
        i = parent(i);
    }
}

