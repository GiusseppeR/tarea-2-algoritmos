set(HPP_LIST "${PROJECT_SOURCE_DIR}/include/Tarea/graph.hpp"
        "${PROJECT_SOURCE_DIR}/include/Tarea/priorityQueue.hpp"
        "${PROJECT_SOURCE_DIR}/include/Tarea/heap.hpp"
        "${PROJECT_SOURCE_DIR}/include/Tarea/fibonacciQueue.hpp")

set(CPP_LIST "Graph.cpp"
        "Heap.cpp"
        "FibonacciQueue.cpp")

add_library(tarea  ${CPP_LIST} ${HPP_LIST})
target_include_directories(tarea PUBLIC ../include)