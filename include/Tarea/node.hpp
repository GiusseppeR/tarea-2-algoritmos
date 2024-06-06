//
// Created by javiera romero orrego on 06-06-24.
//

#ifndef NODE_HPP
#define NODE_HPP

class Node {
public:
    double key;  // nuestra llave será la distancia ya que es lo que importa para prioridad
    int vertex;  //
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    int degree;  // cantidad de hijos
    bool mark;   // si es que ha sido cortado

    Node(double x, int y); // función para inicializar
};

inline Node::Node(double x, int y) {
    key = x;
    vertex = y;
    degree = 0;
    mark = false;
    parent = nullptr;
    child = nullptr;
    left = this;
    right = this;
}

#endif // NODE_HPP