#include <Tarea/fibonacciQueue.hpp>
#include <cmath>
#include <ostream>

void FibonacciQueue::heapify(vector<pair<double, int>> target) {
    for (auto p : target) { //para los valres q nos pasan
        Node* node = new Node(p.first, p.second); //creamos un nodo con el valor de distancia y previos
        nodes[p.second] = node; //lo ponemos en la lista segun su valor
        if (min == nullptr) {
            min = node; //actualizamos el min en caso base
        } else { //si no insertamos como raiz
            min->left->right = node;
            node->left = min->left;
            min->left = node;
            node->right = min;
            if (node->key < min->key) { //y chequeamos si hay q cambiar min
                min = node;
            }
        }
    }
    n = (int) target.size();// la ctda de nodos sera la cantidad q agregamos
}

pair<double, int> FibonacciQueue::getMin() {
    if (min == nullptr)
        return {-1,-1}; //caso vacio
    return {min->key, min->vertex}; //si no devolvemos valores del min
}

pair<double, int> FibonacciQueue::extractMin() {
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
    return {z->key, z->vertex}; //devolvemos z
}

void FibonacciQueue::consolidate() {
    int size = (int)ceil((log2(n))) + 1;
    vector<Node*> A(size, nullptr); //vector q podra contener todos los gardos posibles
    vector<Node*> rootList; //inicializar lista raices
    Node* x = min;
    if (x != nullptr) { //llenar la lista de raices
        do {
            rootList.push_back(x);
            x = x->right;
        } while (x != min); //recorremos desde el minimo hacia las demas raices
    }
    for (Node* root : rootList) { //verificamos para cada raiz
        Node* w = root;
        int d = w->degree;
        while (A[d] != nullptr) { //si ya hay otros arboles guardados de igual grado d debemos unir
            Node* y = A[d]; //Extraemos el previamente guardado
            if (w->key > y->key) swap(w, y);
            link(y, w); //juntamos
            A[d] = nullptr; //se pone en nulo el arbol con grado d q eliminamos
            d++; //actualizar grado en el que guardaremos
        }
        A[d] = w; //agregar nuevo valor con grado correspondiente
    }
    min = nullptr;
    for (Node* y : A) { //reconstruir raices
        if (y != nullptr) { //para los efectivamente guardados agregaremos a la nueva lista
            if (min == nullptr) { //caso base
                min = y;
                min->left = min->right = min;
            }
            else { //si no agregamos reajustando los parametros
                min->left->right = y;
                y->left = min->left;
                min->left = y;
                y->right = min;
                if (y->key < min->key) { //actualizar min de ser necesario
                    min = y;
                }
            }
        }
    }
}

void FibonacciQueue::link(Node* y, Node* x) {
    //eliminar de raices a y
    y->left->right = y->right;
    y->right->left = y->left;
    //asignarlo como hijo de x
    y->parent = x;
    if (x->child == nullptr) {//caso insertar como unico hijo
        x->child = y;
        y->right = y->left = y;
    } else { //si no unirlo a los demas
        x->child->left->right = y;
        y->left = x->child->left;
        x->child->left = y;
        y->right = x->child;
    }
    //ajustar parametros
    x->degree++;
    y->mark = false;
}

void FibonacciQueue::decreaseKey(int p, double distance) {
    Node* x = nodes[p]; //extraer nodo correspondiente
    if (distance > x->key) //caso donde no tiene sentido disminuir
        return;
    x->key = distance; //si no actualizamos la distancia
    Node* y = x->parent;
    if (y != nullptr && x->key < y->key) { //si es necesario reorganizar la lista lo hacemos
        cut(x, y);
        cascadingCut(y);
    }
    if (x->key < min->key) { //actualizar minimo si es el caso
        min = x;
    }
}

void FibonacciQueue::cut(Node* x, Node* y) {
    if (x->right == x) { //caso base para nodo solo
        y->child = nullptr;
    }
    else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x) {
            y->child = x->right;
        }
    }
    y->degree--; //actualizar ctda de nodos conetados
    min->left->right = x; //agregar a lista de nodos y resetear valores
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
            y->mark = true; //primera vez cortando
        }
        else { //si el nodo fue cortado previamente entonces debemos separarlo de su padre
            cut(y, z);
            cascadingCut(z);
        }
    }
}