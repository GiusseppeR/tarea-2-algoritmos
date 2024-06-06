#include <Tarea/graph.hpp>
#include <random>
#include <iostream>
#include <algorithm>

Graph::Graph(int nodes, int edges) {
    random_device rd;
    gen = mt19937(rd());

    adjacencyMatrix.resize(nodes, vector<double>(nodes, 0.0));
    generateConnectedGraph(nodes);
    addEdges(edges - nodes + 1);
}

Graph::Graph(int nodes) : adjacencyMatrix(nodes, vector<double>(nodes, 0.0)) {
    random_device rd;
    gen = mt19937(rd());
}

pair<vector<double>, vector<int>> Graph::dijkstra(PriorityQueue &Q) {
    int nodes = (int) adjacencyMatrix.size();

    vector<double> distances(nodes);
    vector<int> previous(nodes, -1);

    distances[0] = 0;
    for (int i = 1; i < nodes; i++)
        distances[i] = INFINITY;

    vector<pair<double, int>*> pairs = {};

    for (int i = 0; i < nodes; i++){
        auto* p = new pair<double, int>(distances[i], i);
        pairs.push_back(p);
    }

    Q.heapify(pairs);
    while(!Q.isEmpty()){
        pair<double,int>* minPair = Q.extractMin();
        int v = minPair->second;
        for(int u = 0; u < nodes; u++){
            if(u == v)
                continue;
            if(distances[u] > (distances[v] + adjacencyMatrix[u][v]) && adjacencyMatrix[u][v] != 0){
                distances[u] = distances[v] + adjacencyMatrix[u][v];
                previous[u] = v;
                Q.decreaseKey(pairs[u], distances[u]);

            }
        }
    }
    return {distances, previous};
}

void Graph::generateConnectedGraph(int nodes) {
    uniform_real_distribution<> weightGenerator(0.0000001, 1);
    uniform_int_distribution<> nodeSelector(0, nodes);
    
    for (int i = 1; i < nodes; i++) {
        int connectedNode = nodeSelector(gen) % i;
        double weight = weightGenerator(gen);

        adjacencyMatrix[i][connectedNode] = weight;
        adjacencyMatrix[connectedNode][i] = weight;
    }
}

void Graph::addEdges(int edges) {
    uniform_real_distribution<> weightGenerator(0.0000001, 1);
    uniform_int_distribution<> nodeSelector(0, (int) adjacencyMatrix.size() - 1);

    for(int i = 0; i < edges; i++){
        int u = nodeSelector(gen);
        int v = nodeSelector(gen);

        if (u == v || adjacencyMatrix[u][v] != 0)
            continue;

        double weight = weightGenerator(gen);
        adjacencyMatrix[u][v] = weight;
        adjacencyMatrix[v][u] = weight;
    }
}

bool Graph::isConnected() {
    int nodes = (int) adjacencyMatrix.size();
    vector<bool> visited(nodes, false);
    vector<int> stack = {0};

    while ((int)stack.size() != 0){
        int current = stack.back();
        stack.pop_back();

        if (visited[current])
            continue;

        visited[current] = true;
        for (int i = 0; i < nodes; i++){
            if ((adjacencyMatrix[current][i] > 0.0) && !visited[i])
                stack.push_back(i);
        }
    }

    for (int i = 0; i < nodes; i++)
        if (!visited[i]) return false;

    return true;
}