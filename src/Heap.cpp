#include <Tarea/heap.hpp>
#include <utility>

Heap::Heap() = default;
Heap::Heap(vector<pair<int, int>> heapifyTarget) {
    heapData = std::move(heapifyTarget);
}
int Heap::parent(int i) {
    return i/2;
}
int Heap::left(int i) {
    return i*2;
}
int Heap::right(int i) {
    return i*2+1;
}

void Heap::putPair(pair<int, int> pair) {
    heapData.push_back(pair);
}

pair<int, int> Heap::getMin() {
    /*
     * Metodo necesario para extraer el minimo
     */
}
pair<int, int> Heap::extractMin() {}

void Heap::decreaseKey(int node) {}

