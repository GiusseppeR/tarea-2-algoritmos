#include <Tarea/graph.hpp>
#include <random>
#include <iostream>
#include <algorithm>
#include<sstream>

Graph::Graph(int nodes, int edges, std::mt19937 g): adjacencyMatrix(nodes, vector<double>(nodes, 0.0)),
                                                    weightGenerator(0.0000001, 1), nodeSelector(0, nodes - 1){
    gen = g;

    generateConnectedGraph(nodes);
    addEdges(edges - nodes + 1);
}

Graph::Graph(int nodes, int edges): adjacencyMatrix(nodes, vector<double>(nodes, 0.0)),
                                    weightGenerator(0.0000001, 1), nodeSelector(0, nodes - 1){
    random_device rd;
    gen = mt19937(rd());

    generateConnectedGraph(nodes);
    addEdges(edges - nodes + 1);
}

Graph::Graph(int nodes) : adjacencyMatrix(nodes, vector<double>(nodes, 0.0)),
                            weightGenerator(0.0000001, 1), nodeSelector(0, nodes - 1){
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
    for (int i = 0; i < nodes; i++)
        delete pairs[i];
    return {distances, previous};
}

void Graph::generateConnectedGraph(int nodes) {
    for (int i = 1; i < nodes; i++) {
        int connectedNode = nodeSelector(gen) % i;
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
