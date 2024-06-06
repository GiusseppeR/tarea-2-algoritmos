#ifndef TAREALOG_HEAP_HPP
#define TAREALOG_HEAP_HPP
#include <iostream>
#include <Tarea/priorityQueue.hpp>
#include <vector>
#include <utility>
#include <random>
using namespace std;

/**
 * @class Heap
 * @brief Clase que implementa una cola de prioridad utilizando la estructura heap
 */
class Heap : public PriorityQueue{
private:
    size_t heapSize = 0;

    vector<int> nodeIndex;

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
    void minHeapify(int i);

    /**
     *
     * @param node puntero al pair que representa un nodo dentro del heap
     * @return el índice de donde se encuentra el nodo
     */
    int find(pair<double,int>* node);

    /**
     *
     * @param i index of node in array
     * @return metric to compare nodes
     */
    double metric(int i);

public:
    vector<pair<double,int>*> heapData;
    /**
     * @brief Constructor por defecto de la clase Heap
     */
    Heap();

    /**
     * @brief Constructor auxiliar para inicializar el heap con el heapifyTarget
     * @param target Vector en donde se realizará la estructura heap
     */
    Heap(vector<pair<double,int>*> target);

    /**
     * @brief Esta función se encarga de encontrar el par minimo.
     * @return Retorna el contenido el menor par
     */
    pair<double,int>* getMin() override;
    /**
     * @brief Esta función se encarga de encontrar el par minimo y sacarlo de la estructura
     * @return Extrae y retorna el par minimo
     */
    pair<double,int>* extractMin() override;

    /**
     * @brief Esta función se encarga de encontrar un nodo dentro de la estructura y disminuir su valor de la distancia
     * @param node nodo a encontrar en la estructura
     */
    void decreaseKey(pair<double,int>* node, double k) override;
    void printHeap() {
     int n = static_cast<int>(heapSize);
     if (n == 0) {
      cout << "Heap is empty." << endl;
      return;
     }

     int levels = log2(n) + 1; // Número de niveles en el heap

     int index = 0;
     for (int level = 0; level < levels; ++level) {
      int level_count = pow(2, level); // Número de elementos en el nivel actual
      for (int i = 0; i < level_count && index < n; ++i) {
       cout << "(" << heapData[index]->first << ", " << heapData[index]->second << ") ";
       ++index;
      }
      cout << endl;
     }
     cout<<"vector index:\n";
     cout<<"{";
     for (int i=0;i<n;i++) {
      cout<<nodeIndex[i]<<",";
     }
     cout<<"}\n";
    }
};

class TestHeap {
public:
 vector<pair<double,int>*> heapData;
 TestHeap() = default;
 TestHeap(int n) {
  heapData.resize(n);
  // Inicializar el generador de números aleatorios
  random_device rd; // Semilla para el generador
  mt19937 gen(rd()); // Mersenne Twister generator
  uniform_real_distribution<> dis_double(0.0, 100.0); // Distribución para números dobles
  for(int i = 0; i < n; ++i) {
   double random_double = dis_double(gen); // Generar número aleatorio double
   // Crear un nuevo par y añadirlo al vector
   auto* p = new pair<double, int>(random_double, i);
   heapData[i] = p;
  }
 }
 void printHeap() {
  int n = heapData.size();
  if (n == 0) {
   cout << "Heap is empty." << endl;
   return;
  }

  int levels = log2(n) + 1; // Número de niveles en el heap

  int index = 0;
  for (int level = 0; level < levels; ++level) {
   int level_count = pow(2, level); // Número de elementos en el nivel actual
   for (int i = 0; i < level_count && index < n; ++i) {
    cout << "(" << heapData[index]->first << ", " << heapData[index]->second << ") ";
    ++index;
   }
   cout << endl;
  }
 }
 void testHeapConstruction(Heap hp) {
  cout<<"---------------- TEST HEAP CONSTRUCTION ####################\n";
  cout<<"################ ARRAY BEFORE HEAP \n";
  printHeap();
  cout<<"################ ARRAY AFTER HEAP \n";
  hp.printHeap();
  if (checkProperty(hp))
   cout<<"################ CUMPLE CON EL HEAP PROPERTY\n";
  else {
   cout<<"################ NO CUMPLE CON EL HEAP PROPERTY\n";
  }
 }
 void testGetMin(Heap hp) {
 }
 void testExtractMin(Heap hp) {
  cout<<"-------------- PROBANDO TEST_EXTRACT_MIN\n";
  hp.printHeap();
  pair<double,int>* minimo = hp.getMin();
  pair<double,int>* etrMinimo = hp.extractMin();
  if (minimo->first==etrMinimo->first && minimo->second == etrMinimo->second) {
   cout<<"#### SE EXTRAJO EL MINIMO\n";
  }
  else {
   cout<<"#### NO SE EXTRAJO EL MINIMO\n";
  }
  cout<<"###### PROBANDO LA PROPIEDAD DEL HEAP RESULTANTE\n";
  if (checkProperty(hp)) cout<<"### LA PROPIEDAD SE CUMPLE\n";
  hp.printHeap();
 }
 void testDecreaseKey(Heap hp) {
  cout<<"------------------------- Test decrease key ------------------\n";
  hp.printHeap();
  pair<double,int>* ptrd = hp.heapData.back();
  hp.decreaseKey(ptrd,0);
  cout<<"--------------------------------------------------------------\n";
  hp.printHeap();
 }
 void run() {
  const Heap hp(heapData);
  //testHeapConstruction(hp);
  //testExtractMin(hp);
  testDecreaseKey(hp);
 }
 bool checkProperty(Heap hp) {
  int n = hp.heapData.size();
  for (int i = 0; i < n; ++i) {
   int leftChild = 2 * i + 1;
   int rightChild = 2 * i + 2;

   if (leftChild < n) {
    if (hp.heapData[i]->first > hp.heapData[leftChild]->first) {
     return false;
    }
   }

   if (rightChild < n) {
    if (hp.heapData[i]->first > hp.heapData[rightChild]->first) {
     return false;
    }
   }
  }
  return true;
 };
};

#endif //TAREALOG_HEAP_HPP
