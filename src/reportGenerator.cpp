#define _USE_MATH_DEFINES
#include <Tarea/graph.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <Tarea/reportGenerator.hpp>
using namespace std;

void generateReport(vector<int> inputSizes, vector<int> numberOfEdges,
                    vector<double> heapMeanTimes, vector<double> fibonacciMeanTimes,
                    Graph smallestGraph, vector<int> dijkstraResults) {
    std::ofstream file("report.json");
    if(file.is_open()){
        file << (std::string)"{\n";

        file << (std::string)"\"input_sizes\": \"";

        for (int i = 0; i < inputSizes.size(); i++){
            file << (int) inputSizes[i];
            if (i != inputSizes.size() - 1)
                file << (std::string)"+";
        }
        file << (std::string)"\", \n";

        file << (std::string)"\"edges\": \"";

        for (int i = 0; i < numberOfEdges.size(); i++){
            file << (int) numberOfEdges[i];
            if (i != numberOfEdges.size() - 1)
                file << (std::string)"+";
        }
        file << (std::string)"\", \n";

        file << (std::string) "\"example_graph\": \"";

        file << (string) smallestGraph.toString();

        file << (std::string)"\", \n";

        file << (std::string) "\"example_mst\": \"";
        for (int i = 0; i < dijkstraResults.size(); i++){
            file << (int) dijkstraResults[i];
            if (i != dijkstraResults.size() - 1)
                file << (std::string)"+";
        }
        file << (std::string)"\", \n";

        file << (std::string) "\"heap_mean_times\": \"";

        for (int i = 0; i < heapMeanTimes.size(); i++){
            file << (double) heapMeanTimes[i];
            if (i != heapMeanTimes.size() - 1)
                file << (std::string)"+";
        }
        file << (std::string)"\", \n";

        file << (std::string) "\"fq_mean_times\": \"";

        for (int i = 0; i < fibonacciMeanTimes.size(); i++){
            file << (double) fibonacciMeanTimes[i];
            if (i != fibonacciMeanTimes.size() - 1)
                file << (std::string)"+";
        }
        file << (std::string) "\" \n";
        file << (std::string) "}";

        file.close();
    }
}
