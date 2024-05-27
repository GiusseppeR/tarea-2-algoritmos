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
    int heapSize = 0;
    vector<pair<int,int>> heapData;

    /**
     * @brief Calcula el nodo padre del hijo i
     * @param i nodo de consulta
     * @return el indice del nodo padre
     */
    static int parent(int i);
    /**
     * @brief Calcula el nodo del hijo izquierdo
     * @param i nodo de consulta
     * @return el índice del nodo hijo izquierdo
     */
    static int left(int i);
    /**
     * @brief Calcula el nodo del hijo derecho
     * @param i nodo de consulta
     * @return el índice del nodo hijo derecho
     */
    static int right(int i);

    /**
     * @brief Mantiene la propiedad del heap en O(log n)
     */
    void maxHeapify();

    /**
     * @brief Crea un max-heap desde un input array desordenado en O(n)
     */
    void buildMaxHeap();

    /**
     * @brief Ordena el array en O(n log n)
     */
    void heapsort();

    /*
     * En genaral cada una de las funciones están hechas para crear la estructura del
     * priority queue corre en O(log n) más el tiempo de mapeo que hay al insertar
     * objetos en la priority queue e indices en el heap.
     */
    void maxHeapInsert();
    void maxHeapExtractMax();
    void maxHeapIncreaseKey();
    void maxHeapMaximum();

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
