#ifndef TAREALOG_QUERY_H
#define TAREALOG_QUERY_H

#include <chrono>
#include "Tarea/reportGenerator.hpp"
#include "Tarea/fibonacciQueue.hpp"
#include "Tarea/graph.hpp"
#include "Tarea/heap.hpp"

void generate_experiment() {
    const vector<int> i_values = {10, 12, 14};
    const vector<int> j_values = {16, 17, 18, 19, 20, 21, 22};
    const int repeat = 50;

    vector<int> inputSizes;
    vector<int> numberOfEdges;
    vector<double> heapMeanTimes;
    vector<double> fibonacciMeanTimes;

    inputSizes.reserve(i_values.size());
    numberOfEdges.reserve(i_values.size() * j_values.size());
    heapMeanTimes.reserve(i_values.size() * j_values.size());
    fibonacciMeanTimes.reserve(i_values.size() * j_values.size());

    for (int i : i_values) {
        int v = 1 << i;
        inputSizes.push_back(v);

        for (int j : j_values) {
            if(i == 10 && j > 18)
                continue;

            int e = 1 << j;
            numberOfEdges.push_back(e);

            double meanHeap = 0;
            double meanFib = 0;

            for (int c = 0; c < repeat; c++) {
                Graph graph(v, e);

                FibonacciQueue Q;
                auto start = chrono::high_resolution_clock::now();
                auto result1 = graph.dijkstra(Q);
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration1 = end - start;
                meanHeap += duration1.count();

                Heap Q2;
                start = chrono::high_resolution_clock::now();
                auto result2 = graph.dijkstra(Q2);
                end = chrono::high_resolution_clock::now();
                chrono::duration<double> duration2 = end - start;
                meanFib += duration2.count();
            }

            meanHeap /= repeat;
            meanFib /= repeat;
            heapMeanTimes.push_back(meanHeap);
            fibonacciMeanTimes.push_back(meanFib);


            cout << "Pair (" << i << "," << j << ") completed\n"
                 << "mean Heap time: " << meanHeap << " seconds\n"
                 << "mean Fib time: " << meanFib << " seconds\n"
                 << "**************************************************\n";
        }
    }

    Heap Q;
    Graph smallest(1 << 10, 1 << 16);
    vector<int> mstSmallest = smallest.dijkstra(Q).second;
    generateReport(inputSizes, numberOfEdges, heapMeanTimes, fibonacciMeanTimes, smallest, mstSmallest);
}
#endif
