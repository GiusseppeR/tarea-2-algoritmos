#ifndef TAREALOG_QUERY_H
#define TAREALOG_QUERY_H

#include <chrono>
#include "Tarea/reportGenerator.hpp"
#include "Tarea/fibonacciQueue.hpp"
#include "Tarea/graph.hpp"
#include "Tarea/heap.hpp"

void generate_experiment(){
    random_device rd;
    mt19937 gen(rd());

    const vector<int> i_values = {10, 12, 14};
    const vector<int> j_values = {16, 17, 18, 19, 20, 21, 22};
    const int repeat = 50;

    vector<int> inputSizes;
    vector<int> numberOfEdges;
    vector<double> heapMeanTimes;
    vector<double> fibonacciMeanTimes;
    
    for (int i : i_values) {
        int v = 1 << i;
        inputSizes.push_back(v);

        for (int j : j_values) {
            int e = 1 << j;
            numberOfEdges.push_back(e);

            double meanHeap = 0;
            double meanFib = 0;

            for (int c = 0; c < repeat; c++) {
                Graph graph = Graph(v, e, gen); //creamos grafo con aristas
                FibonacciQueue Q = FibonacciQueue();
                auto start1 = chrono::high_resolution_clock::now();
                auto result1 = graph.dijkstra(Q);
                auto end1 = chrono::high_resolution_clock::now();
                chrono::duration<double> duration1 = end1 - start1;
                meanHeap += duration1.count();

                Heap Q2= Heap();
                auto start2 = chrono::high_resolution_clock::now();
                auto result2 = graph.dijkstra(Q2);
                auto end2 = chrono::high_resolution_clock::now();
                chrono::duration<double> duration2 = end2 - start2;
                meanFib += duration2.count();

            }
            heapMeanTimes.push_back(meanHeap/50.0);
            fibonacciMeanTimes.push_back(meanFib/50.0);
            cout << "Pair (" << i << "," << j << ") completed" << endl;
            cout << "mean Heap time: " << meanHeap/50.0 << " seconds" << endl;
            cout << "mean Fib time: " << meanFib/50.0 << " seconds" << endl;
            cout << "**************************************************" << endl;
        }
    }
    Heap Q = Heap();
    Graph smallest = Graph(1<<10,1<<16);
    vector<int> mstSmallest = smallest.dijkstra(Q).second;
    generateReport(inputSizes,numberOfEdges,heapMeanTimes,fibonacciMeanTimes,smallest,mstSmallest);
}
#endif //TAREALOG_QUERY_H
