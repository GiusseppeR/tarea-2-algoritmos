#include<iostream>
#include <Tarea/graph.hpp>
#include <algorithm>
#include <Tarea/priorityQueue.hpp>

int main(){
    Graph graph = Graph(1024, 65536);
    cout << "Graph generated" << endl;
    TestPQ Q = TestPQ();
    auto result = graph.dijkstra(Q);

    for(int i = 0; i < 1024; i++){
        cout << "(" << result.first[i] << "," << result.second[i] << ")" << endl;
    }
    return 0;
}
