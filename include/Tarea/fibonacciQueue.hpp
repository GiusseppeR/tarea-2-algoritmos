#ifndef TAREALOG_FIBONACCIQUEUE_HPP
#define TAREALOG_FIBONACCIQUEUE_HPP

#include <unordered_map>
#include <Tarea/priorityQueue.hpp>
#include <vector>

using namespace std;
//estructura para cada nodo
struct FibonacciNode {
    int key;
    int distance;
    int degree;
    bool marked;
    FibonacciNode* parent;
    FibonacciNode* child;
    FibonacciNode* l;
    FibonacciNode* r;
    //constructor q inicializa el nodo con la llave y distancia q se le de
    //los demas parametros son los iniciales para un nodo aislado
    FibonacciNode(int x, int y):
        key(x),
        distance(y),
        degree(0),
        marked(false),
        parent(nullptr),
        child(nullptr),
        l(this), //su derecha e izquierda son el mismo para cualquier nodo aisaldo
        r(this)
    {}
};
class FibonacciQueue : public PriorityQueue{
private:
    FibonacciNode* min; //puntero al valor minimo distancia menor
    int c; //contador para saber cuantos nodos hay en la estructura
    unordered_map<int, FibonacciNode*> elements; //primer parameto sera su identificador (key)para acceder con facilidad
    //cualquier método extra, hacerlo privado
    void link(FibonacciNode* x, FibonacciNode* y); //une el arbol de raiz x con el de raiz y
    void cut(FibonacciNode* x, FibonacciNode* y ); // poda x de su padre y
public:
    FibonacciQueue();
    void heapify(vector<pair<int,int>> target) override;
    pair<int,int> getMin() override;
    pair<int,int> extractMin() override;
    void decreaseKey(int node) override;
};

#endif
