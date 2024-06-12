#ifndef GRAPH_H
#define GRAPH_H

#include <Tarea/priorityQueue.hpp>
#include <vector>
#include <random>
#include <functional>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

class Graph {
private:
    vector<vector<double>> adjacencyMatrix;
    mt19937 gen;

    void generateConnectedGraph(int nodes);
    void addEdges(int edges);
    string vectorToString(vector<double> target);
public:
    Graph(int nodes, int edges);
    Graph(int nodes);
    bool isConnected();
    pair<vector<double>, vector<int>> dijkstra(PriorityQueue& Q);
    string toString();
};

#endif
