#include <Tarea/graph.hpp>
#include <random>
#include <iostream>
#include <algorithm>
#include<sstream>

Graph::Graph(int nodes, int edges): adjacencyMatrix(nodes, vector<double>(nodes, 0.0)),
                                    weightGenerator(0.0000001, 1), nodeSelector(0, nodes - 1){
    random_device rd;
    gen = mt19937(rd());

    generateConnectedGraph(nodes);
    addEdges(edges - nodes + 1);
}

Graph::Graph() = default;

pair<vector<double>, vector<int>> Graph::dijkstra(PriorityQueue &Q) {
    int nodes = (int) adjacencyMatrix.size();
    vector<double> distances(nodes, INFINITY);
    vector<int> previous(nodes, -1);

    distances[0] = 0;

    vector<pair<double, int>> pairs(nodes);
    for(int i = 0; i < nodes; i++)
        pairs[i] = {distances[i],i};

    Q.heapify(pairs);

    while(!Q.isEmpty()){
        pair<double,int> minPair = Q.extractMin();
        int v = minPair.second;
        for(int u = 0; u < nodes; u++){
            if(u == v)
                continue;
            if(distances[u] > (distances[v] + adjacencyMatrix[u][v]) && adjacencyMatrix[u][v] != 0){
                distances[u] = distances[v] + adjacencyMatrix[u][v];
                previous[u] = v;
                Q.decreaseKey(u, distances[u]);
            }
        }
    }

    return {distances, previous};
}

void Graph::generateConnectedGraph(int nodes) {
    for (int i = 1; i < nodes; i++) {
        uniform_int_distribution<> nodeRange(0,i-1);
        int connectedNode = nodeRange(gen);
        double weight = weightGenerator(gen);

        adjacencyMatrix[i][connectedNode] = weight;
        adjacencyMatrix[connectedNode][i] = weight;
    }
}

void Graph::addEdges(int edges) {
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
string Graph::vectorToString(vector<double> target) {
    std::ostringstream os;
    for(double i : target){
        os << i << ",";
    }
    string result = os.str();
    result.pop_back();
    return result;
}
string Graph::toString(){
    string result;
    for (const auto & i : adjacencyMatrix){
        result += vectorToString(i);
        result += ";";
    }
    result.pop_back();
    return result;
}
