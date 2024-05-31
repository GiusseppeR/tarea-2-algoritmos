#include <Tarea/heap.hpp>
#include <utility>
#include <algorithm>
#include <stdexcept>

Heap::Heap() = default;

Heap::Heap(vector<pair<int, int>> heapifyTarget) {
    heapData = heapifyTarget;
    heapSize = heapifyTarget.size();
    printf("%i\n",heapSize);
    int i = (static_cast<int>(heapSize)/2) - 1;
    printf("%i\n",i);
    while (i>=0) {
        minHeapify(i);
        i--;
    }

}
int Heap::parent(int i) {
    return i/2;
}
int Heap::left(int i) {
    return i*2+1;
}
int Heap::right(int i) {
    return i*2+2;
}
int Heap::distanceInNode(int i) {
    printf("muere?\n");
    int distance = heapData[i].first;
    printf("distance of node %i: %i\n",i,distance);
    return distance;
}
void Heap::putPair(pair<int, int> pair) {
    heapData.push_back(pair);
}

void Heap::minHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest;
    printf("%i,%i\n",l,r);
    if (l <= heapSize && distanceInNode(l)<distanceInNode(i)) {
        smallest = l;
    } else {
        smallest = i;
    }
    if (r<=heapSize && distanceInNode(r)<distanceInNode(smallest)) {
        smallest = r;
    }
    if (smallest != i) {
        swap(heapData[i],heapData[smallest]);
        minHeapify(smallest);
    }
}




pair<int, int> Heap::getMin() {
    return heapData[0];
}
pair<int, int> Heap::extractMin() {
    pair<int,int> min = getMin();
    const pair<int,int> last = heapData[heapSize-1];
    heapData.pop_back();
    heapData[0] = last;
    minHeapify(0);
    return min;
}

int Heap::find(int node) {
    if (node > heapSize) {
        throw std::runtime_error("Node out of index");
    }
    if (nodeIndex[node] == -1) {
        throw std::runtime_error("Node dosen't exit in array");
    }
    return nodeIndex[node];

}

void Heap::decreaseKey(int node, int k) {
    int i = find(node);
    if (heapData[i].first < k) {
        return ;
    }
    heapData[i].first = k;
    while (i>0 && heapData[parent(i)].first < heapData[i].first) {
        swap(heapData[i],heapData[parent(i)]);
        i = parent(i);
    }
}

