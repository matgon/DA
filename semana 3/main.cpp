
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <limits>

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
class ComparaPilas {
public:
    bool operator()(const std::stack<int>& a, const std::stack<int>& b) {
        return a.top() > b.top();
    }
};

int resolver(std::priority_queue<std::stack<int>, std::vector<std::stack<int>>, ComparaPilas>& colaMinimos, int minimo) {
    bool encontrado = false;
    int contador = 0;

    while (!encontrado) {
        int sacado = colaMinimos.top().top();
        if (sacado == minimo)
            encontrado = true;
        contador++;

        std::stack<int> aux = colaMinimos.top();
        colaMinimos.pop();
        aux.pop();
        if (!aux.empty()) {
            colaMinimos.push(aux);
        }
    }

    return contador;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int pilas;
    int minimo = -1;
    std::priority_queue<std::stack<int>, std::vector<std::stack<int>>, ComparaPilas> colaMinimos;

    std::cin >> pilas;
    if (!std::cin)
        return false;

    if (!std::cin)  // fin de la entrada
        return false;

    for (int i = 0; i < pilas; i++) {
        int comics;
        std::stack<int> s;
        std::cin >> comics;
        for (int j = 0; j < comics; j++) {
            int aux;
            std::cin >> aux;
            if (aux < minimo || minimo == -1)
                minimo = aux;
            s.push(aux);
        }
        colaMinimos.push(s);
    }

    int sol = resolver(colaMinimos, minimo);

    // escribir sol
    std::cout << sol << std::endl;

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
/*#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif*/

    while (resuelveCaso());

    // para dejar todo como estaba al principio
/*#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif*/
    return 0;
}
