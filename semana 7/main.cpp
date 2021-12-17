
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

struct tSol {
    int coste;
    int numAeropuertos;
} ;


template <typename Valor>
class Aeropuerto {
private:

    std::vector<Arista<Valor>> _ARM;
    Valor coste;
    int numAeropuertos;

public:

    Valor costeARM() const {
        return coste;
    }

    Valor numAeropuetos() const {
        return numAeropuertos;
    }

    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }

    Aeropuerto(GrafoValorado<Valor> const& g, int costeInicial, int costeAeropuerto, int aeropuertos) : coste(costeInicial), numAeropuertos(aeropuertos){

        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());

        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                if (a.valor() < costeAeropuerto) {
                    _ARM.push_back(a);
                    numAeropuertos -= 1;
                    coste -= costeAeropuerto;
                    coste += a.valor();
                }
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
tSol resolver(const GrafoValorado<int>& datos, int costeInicial, int costeAeropuerto) {
    tSol sol;

    Aeropuerto<int> arm(datos, costeInicial, costeAeropuerto, datos.V());

    sol.coste = arm.costeARM();
    sol.numAeropuertos = arm.numAeropuetos();

    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int n, m, a;
    std::cin >> n >> m >> a;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> aeropuerto(n);
    int c1, c2, coste;

    for (int i = 0; i < m; i++) {
        std::cin >> c1 >> c2 >> coste;
        Arista<int> arista(c1-1, c2-1, coste);
        aeropuerto.ponArista(arista);
    }

    tSol sol = resolver(aeropuerto, a * n, a);

    // escribir sol

    std::cout << sol.coste << " " << sol.numAeropuertos << std::endl;

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
