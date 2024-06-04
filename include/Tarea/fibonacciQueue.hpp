#ifndef TAREALOG_FIBONACCIQUEUE_HPP
#define TAREALOG_FIBONACCIQUEUE_HPP

#include <unordered_map>
#include <Tarea/priorityQueue.hpp>
#include <vector>

using namespace std;
//estructura para cada nodo
struct FibonacciNode {
    int key;
    double distance;
    int degree;
    bool marked;
    FibonacciNode* parent;
    FibonacciNode* child;
    FibonacciNode* l;
    FibonacciNode* r;
    //constructor q inicializa el nodo con la llave y distancia q se le de
    //los demas parametros son los iniciales para un nodo aislado
    FibonacciNode(int x, double y):
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
    void link(FibonacciNode* y, FibonacciNode* x); //une el arbol de raiz x con el de raiz y
    void cut(FibonacciNode* x, FibonacciNode* y ); // poda x de su padre y
    void insert(int node, double dist);
    void adjust();
    void propagatingCut(FibonacciNode* y);
public:
    FibonacciQueue();
    void heapify(vector<pair<double,int>*> target) override;
    pair<double,int>* getMin() override;
    pair<double,int>* extractMin() override;
    void decreaseKey(pair<double, int>* node, double newDist) override;
    bool isEmpty() const override;
};

#endif
