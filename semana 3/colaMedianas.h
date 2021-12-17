#ifndef COLAMEDIANAS_H_
#define COLAMEDIANAS_H_

#include <queue>
#include <vector>

class ColaMedianas {
public:

    ColaMedianas() {}

    void insertar(int x) {
        if (!colaMinimos.empty() && colaMinimos.top() < x) {
            colaMinimos.push(x);
        }
        else if (!colaMaximos.empty() && colaMaximos.top() > x) {
            colaMaximos.push(x);
        }
        else {
            colaMaximos.push(x);
        }
        reequilibrar();
    }

    void reequilibrar() {

        //se comparan los tamaños de ambas colas. Si es igual, o la diferencia de tamaños es mayor que 1, no se hace nada. Si es mayor o menos que 1, se reajustan los tamaños

        if (isBalanced() > 1) {
            colaMinimos.push(colaMaximos.top());
            colaMaximos.pop();
        }
        else if (isBalanced() < -1) {
            colaMaximos.push(colaMinimos.top());
            colaMinimos.pop();
        }
    }

    int isBalanced() {
        return colaMaximos.size() - colaMinimos.size();
    }

    bool vacia() const {
        return colaMaximos.empty() && colaMinimos.empty();
    }

    int mediana() const {

        int mediana;
        int medianaPos = (colaMinimos.size() + colaMaximos.size() + 1) / 2;

        //si el tamaño de la colaMayores es mayor que la mediana, se devuelve el elemento top de esa cola
        if (medianaPos <= colaMaximos.size()) {

            mediana = colaMaximos.top();
        }

        //si no, se devuelve el de la cola de minimos
        else {

            mediana = colaMinimos.top();
        }

        return mediana;
    }

    void quitarMediana() {

        int medianaPos = (colaMinimos.size() + colaMaximos.size() + 1) / 2;

        //si el tamaño de la colaMayores es mayor que la mediana, se elimina el elemento que este en top en esa cola
        if (medianaPos <= colaMaximos.size()) {

            colaMaximos.pop();
        }

        //si no, se elimina el de la cola de minimos
        else {

            colaMinimos.pop();
        }


        reequilibrar();
    }

private:

    std::priority_queue<int, std::vector<int>, std::less<int>> colaMaximos; //guarda los elementos menores o iguales que la mediana
    std::priority_queue<int, std::vector<int>, std::greater<int>> colaMinimos; //guarda los elementos mayores que la mediana

};
#endif /* INDEXPQ_H_ */