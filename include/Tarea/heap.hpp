#ifndef TAREALOG_HEAP_HPP
#define TAREALOG_HEAP_HPP

#include <Tarea/priorityQueue.hpp>
#include <vector>

using namespace std;

/**
 * @class Heap
 * @brief Clase que implementa una cola de prioridad utilizando la estructura heap
 */
class Heap : public PriorityQueue{
private:
    vector<pair<int,int>> heapData;
public:
    /**
     * @brief Constructor por defecto de la clase Heap
     */
    Heap();

    /**
     * @brief Constructor auxiliar para inicializar el heap con el heapifyTarget
     * @param heapifyTarget Vector en donde se realizará la estructura heap
     */
    Heap(vector<pair<int,int>> heapifyTarget);

    /**
     * @brief Esta función se encarga de encontrar el par minimo.
     * @return Retorna el contenido el menor par
     */
    pair<int,int> getMin() override;
    /**
     * @brief Esta función se encarga de encontrar el par minimo y sacarlo de la estructura
     * @return Extrae y retorna el par minimo
     */
    pair<int,int> extractMin() override;
    /**
     * @brief Función que se encarga de meter un nuevo par a la estructura.
     * @param pair Par de datos a guardar
     */
    void putPair(pair<int,int> pair);

    /**
     * @brief Esta función se encarga de encontrar un nodo dentro de la estructura y disminuir su valor de la distancia
     * @param node nodo a encontrar en la estructura
     */
    void decreaseKey(int node) override;
};

#endif //TAREALOG_HEAP_HPP
