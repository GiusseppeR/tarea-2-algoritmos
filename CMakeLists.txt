cmake_minimum_required(VERSION 3.16.3)
project(TareaLog)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} main.cpp
        include/Tarea/node.hpp
        include/query/query.hpp
        include/query/query.cpp)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} tarea)