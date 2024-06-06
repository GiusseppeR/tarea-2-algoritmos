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
public:
    Graph(int nodes, int edges);
    Graph(int nodes);
    bool isConnected();
    pair<vector<double>, vector<int>> dijkstra(PriorityQueue& Q);
};

class TestPQ : public PriorityQueue{
private:
    vector<pair<double,int>*> queue;
public:
    TestPQ() = default;
    void heapify(vector<pair<double, int> *> target) override{
        for (auto ptr : target)
            queue.push_back(ptr);

        sort(queue.begin(), queue.end(), [](pair<double, int> *a, pair<double, int> *b) {
            return (*a).first < (*b).first;
        });
        reverse(queue.begin(), queue.end());
    }
    pair<double, int> * getMin() override{
        return queue.back();
    }
    pair<double, int> * extractMin() {
        auto result = queue.back();
        queue.pop_back();
        return result;
    };
    void decreaseKey(pair<double, int> *p, double distance) override{
        auto index = find(queue.begin(),queue.end(),p) - queue.begin();
        queue[index]->first = distance;
        sort(queue.begin(), queue.end(), [](pair<double, int> *a, pair<double, int> *b) {
            return (*a).first < (*b).first;
        });
        reverse(queue.begin(), queue.end());
    };
    bool isEmpty() override{
        return queue.empty();
    }
};

#endif
