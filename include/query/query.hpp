
#ifndef QUERY_H
#define QUERY_H

#include <cmath>
#include "time.h"
#include "Tarea/fibonacciQueue.hpp"
#include "Tarea/graph.hpp"
#include "Tarea/heap.hpp"

void generate_experiment(){
    const vector<int> i_values = {10, 12, 14};
    const vector<int> j_values = {16, 17, 18, 19, 20, 21, 22};
    const int repeat = 50;
    for (int i : i_values) {
        int v = pow(2,i);
        for (int j : j_values) {
            int e = pow(2,j);
            for (int c = 0; c < repeat; ++c) {
                Graph graph = Graph(v, e); //creamos grafo con aristas
                FibonacciQueue Q = FibonacciQueue();
                auto start1 = clock();
                auto result1 = graph.dijkstra(Q);
                auto end1 = clock();
                double duration1 = double(end1 - start1) / CLOCKS_PER_SEC;
                cout << "Experiment with v=" << v << " e=" << e << " repetition number " << c+1<< endl;
                cout << "FibonacciQueue: " << duration1 << " seconds" << endl;

                Heap Q2= Heap();
                auto start2 = clock();
                auto result2 = graph.dijkstra(Q2);
                auto end2 = clock();
                double duration2= double(end2 - start2) / CLOCKS_PER_SEC;
                cout << "Heap: " << duration2 << " seconds" << endl;
                cout << "******************************************************" << endl;
            }
        }
    }
}
#endif //QUERY_H
