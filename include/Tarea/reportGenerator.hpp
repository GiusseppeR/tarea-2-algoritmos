#ifndef TAREALOG_REPORTGENERATOR_HPP
#define TAREALOG_REPORTGENERATOR_HPP

#include <Tarea/graph.hpp>
void generateReport(vector<int> inputSizes, vector<int> numberOfEdges,
                    vector<double> heapMeanTimes, vector<double> fibonacciMeanTimes,
                    Graph smallestGraph, vector<int> dijkstraResults);
#endif
