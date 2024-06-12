#include<iostream>
#include <Tarea/graph.hpp>
#include <Tarea/reportGenerator.hpp>

#include "Tarea/fibonacciQueue.hpp"

int main(){
    Graph graph = Graph(1024, 1<<16);
    cout << "Graph fib generated" << endl;
    FibonacciQueue Q =  FibonacciQueue();
    auto result = graph.dijkstra(Q);

    generateReport({1024},{1<<16,1<<17,1<<18,1<<19,1<<20,1<<21,1<<22},{0.1,0.1,0.1,0.1,0.1,0.1,0.1},{1.1,1.1,1.1,1.1,1.1,1.1,1.1},graph,result.second);
    return 0;
}
