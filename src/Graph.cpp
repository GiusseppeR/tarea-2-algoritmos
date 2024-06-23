#include <Tarea/graph.hpp>
#include <random>
#include <iostream>
#include <algorithm>
#include<sstream>

Graph::Graph(int nodes, int edges): adjacencyMatrix(nodes, vector<double>(nodes, 0.0)),
                                    weightGenerator(0.0000001, 1), nodeSelector(0, nodes - 1),
                                    connections(nodes, vector<int>()){
    random_device rd;
    gen = mt19937(rd());

    generateConnectedGraph(nodes);
    addEdges(edges - nodes + 1);
}

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
        for(int i = 0; i < connections[v].size(); i++){
            int u = connections[v][i];

            if(distances[u] <= (distances[v] + adjacencyMatrix[u][v]) )
                continue;

            distances[u] = distances[v] + adjacencyMatrix[u][v];
            previous[u] = v;
            Q.decreaseKey(u, distances[u]);
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

        connections[i].push_back(connectedNode);
        connections[connectedNode].push_back(i);
    }
}

void Graph::addEdges(int edges) {
    for(int i = 0; i < edges; i++){
        int u = nodeSelector(gen);
        int v;

        do {
            v = nodeSelector(gen);
        } while(u == v || adjacencyMatrix[u][v] != 0);

        double weight = weightGenerator(gen);
        adjacencyMatrix[u][v] = weight;
        adjacencyMatrix[v][u] = weight;

        connections[u].push_back(v);
        connections[v].push_back(u);
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
