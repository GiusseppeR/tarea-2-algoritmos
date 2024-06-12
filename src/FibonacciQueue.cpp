#include <Tarea/fibonacciQueue.hpp>
#include <cmath>
#include <iostream>
#include <limits>
#include <ostream>

void FibonacciQueue::heapify(vector<pair<double, int>*> target) {
    for (auto p : target) { //para los valres q nos pasan
        Node* node = new Node(p->first, p->second); //creamos un nodo con el valor de distancia y previos
        nodes[p->second] = node; //lo ponemos en la lista segun su valor
        if (min == nullptr) {
            min = node; //actualizamos el min en caso base
        } else { //si no reordenamos
            min->left->right = node;
            node->left = min->left;
            min->left = node;
            node->right = min;
            if (node->key < min->key) { //y chequeamos si hay q cambiar min
                min = node;
            }
        }
    }
    n = target.size();// la ctda de nodos sera la cantidad q agregamos
}

pair<double, int>* FibonacciQueue::getMin() {
    if (min == nullptr) return nullptr; //caso vacio
    return new pair<double, int>(min->key, min->vertex); //si no devolvemos valores del min
}

pair<double, int>* FibonacciQueue::extractMin() {
    Node* z = min; //traemos puntero del minimo
    if (z != nullptr) { //caso no vacio
        if (z->child != nullptr) { //si tiene hijos debemos agregarlos a las raices
            Node* x = z->child;
            do { //actualizamos sus der e izq y eliminamos el padre
                Node* next = x->right;
                min->left->right = x;
                x->left = min->left;
                min->left = x;
                x->right = min;
                x->parent = nullptr;
                x = next;
            } while (x != z->child);
        }
        //eliminamos z de las raices
        z->left->right = z->right;
        z->right->left = z->left;
        //actualizamos el min y reorganizamos la lista de raices en caso de ser necesario
        if (z == z->right) {
            min = nullptr;
        } else {
            min = z->right;
            consolidate();
        }
        n--; //diminuye ctda al extraer z
    }
    return new pair<double, int>(z->key, z->vertex); //devolvemos z
}

void FibonacciQueue::consolidate() {
    int size = (int)ceil((log2(n))) + 1;
    vector<Node*> A(size, nullptr);
    vector<Node*> rootList;
    Node* x = min;
    if (x != nullptr) {
        do {
            rootList.push_back(x);
            x = x->right;
        } while (x != min);
    }
    for (Node* root : rootList) {
        Node* x = root;
        int d = x->degree;
        while (A[d] != nullptr) {
            Node* y = A[d];
            if (x->key > y->key) swap(x, y);
            link(y, x);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
    }
    min = nullptr;
    for (Node* y : A) {
        if (y != nullptr) {
            if (min == nullptr) {
                min = y;
                min->left = min->right = min;
            }
            else {
                min->left->right = y;
                y->left = min->left;
                min->left = y;
                y->right = min;
                if (y->key < min->key) {
                    min = y;
                }
            }
        }
    }
}

void FibonacciQueue::link(Node* y, Node* x) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child == nullptr) {
        x->child = y;
        y->right = y->left = y;
    } else {
        x->child->left->right = y;
        y->left = x->child->left;
        x->child->left = y;
        y->right = x->child;
    }
    x->degree++;
    y->mark = false;
}

void FibonacciQueue::decreaseKey(pair<double, int>* p, double distance) {
    Node* x = nodes[p->second];
    if (distance > x->key)
        return;
    x->key = distance;
    Node* y = x->parent;
    if (y != nullptr && x->key < y->key) {
        cut(x, y);
        cascadingCut(y);
    }
    if (x->key < min->key) {
        min = x;
    }
}

void FibonacciQueue::cut(Node* x, Node* y) {
    if (x->right == x) {
        y->child = nullptr;
    }
    else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x) {
            y->child = x->right;
        }
    }
    y->degree--;
    min->left->right = x;
    x->left = min->left;
    min->left = x;
    x->right = min;
    x->parent = nullptr;
    x->mark = false;
}

void FibonacciQueue::cascadingCut(Node* y) {
    Node* z = y->parent;
    if (z != nullptr) {
        if (!y->mark) {
            y->mark = true;
        }
        else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}