cmake_minimum_required(VERSION 3.16.3)
project(TareaLog)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -g")
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} tarea)