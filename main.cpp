#include<iostream>
#include <Tarea/graph.hpp>
#include <algorithm>
#include <Tarea/priorityQueue.hpp>

#include "Tarea/fibonacciQueue.hpp"

int main(){
    Graph graph = Graph(1024, 65536);
    cout << "Graph test generated" << endl;
    TestPQ Q1 = TestPQ();
    auto result1 = graph.dijkstra(Q1);

    for(int i = 0; i < 1024; i++){
        cout << "(" << result1.first[i] << "," << result1.second[i] << ")" << endl;
    }
    cout << "***********************************************************************" << endl;
    cout << "Graph fib generated" << endl;
    FibonacciQueue Q =  FibonacciQueue();
    auto result = graph.dijkstra(Q);

    for(int i = 0; i < 1024; i++){
        cout << "(" << result.first[i] << "," << result.second[i] << ")" << endl;
    }
    return 0;
}
