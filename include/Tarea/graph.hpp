#ifndef GRAPH_H
#define GRAPH_H

#include <Tarea/priorityQueue.hpp>
#include <vector>

using namespace std;

class Graph {
private:
    //variables
public:
    Graph();
    vector<pair<int, int>> dijkstra(PriorityQueue& Q);
};

#endif
